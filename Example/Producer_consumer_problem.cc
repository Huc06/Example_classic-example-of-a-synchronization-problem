#include <iostream>
#include <queue>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

// Hàng đợi (queue) nơi producer (nhà sản xuất) thêm dữ liệu và consumer (người tiêu dùng) lấy dữ liệu từ đó
queue<long> dataQ; 

// Một mutex dùng để đồng bộ giữa producer và consumer, mutex còn lại để đồng bộ in ra màn hình
mutex pc_mu, print_mu; 

// Biến điều kiện để đồng bộ giữa producer và consumer
condition_variable consumerwait_cv; 


void Print(string str)
{
	// Đảm bảo rằng các lệnh in ra được thực hiện tuần tự, tránh bị chồng lấn
	lock_guard<mutex> lg(print_mu); 
	cout << str << endl;
}

void Producer()
{
	int index = 0;
	while (1)
	{
		unique_lock<mutex> ul(pc_mu);

		// Nếu hàng đợi chứa nhiều hơn 4 phần tử chưa được xử lý,
		// đợi một chút trước khi thêm dữ liệu mới vào
		if (dataQ.size() >= 5) 
		{
			consumerwait_cv.wait(ul, []() {return !(dataQ.size() >= 5); });
		}

		dataQ.push(index);
		// Mở khóa mutex và thông báo cho consumer rằng đã có dữ liệu
		ul.unlock(); 
		consumerwait_cv.notify_one();
		// Tạo một độ trễ ngẫu nhiên
		this_thread::sleep_for(chrono::milliseconds(100)); 

		Print(" Producer produced " + to_string(index));

		index++;
	}
}

void Consumer()
{
	while (1)
	{
		unique_lock<mutex> ul(pc_mu);
		if (dataQ.empty()) // Nếu hàng đợi trống,
		{
			// Chờ producer thêm dữ liệu vào
			// Điều kiện kiểm tra phải trả về false để tiếp tục chờ đợi.
			// Vì vậy, nếu hàng đợi trống, điều kiện nên trả về false (!q.empty())
			consumerwait_cv.wait(ul, []() {return !dataQ.empty(); }); 
		}

		ul.unlock(); // Mở khóa mutex để producer không bị chặn.
		// Nếu bỏ dòng này, producer sẽ bị khóa cho đến khi vòng lặp này kết thúc
		
		int element = dataQ.front(); // Lấy phần tử từ hàng đợi
		dataQ.pop();

		consumerwait_cv.notify_one(); // Thông báo cho producer rằng có thể tiếp tục 
		// vì một phần tử đã được lấy ra để xử lý

		// Chờ một khoảng thời gian để mô phỏng việc consumer chậm hơn producer
		this_thread::sleep_for(chrono::milliseconds(1000)); 
		Print(" Consumer got " + to_string(element));
	}
}


int main()
{
	thread prod(Producer);
	thread cons(Consumer);

	prod.detach();
	cons.detach();

	// Chạy vòng lặp vô tận để quan sát producer và consumer hoạt động
	while (1); 
}

// author: Pradeep P
// References: https://www.pradeepbangalore.in/post/producer-consumer-problem-c-solution-using-condition-variables