// 18_readers_writers_01.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

mutex resource_mutex; // Mutex để bảo vệ quyền truy cập tài nguyên dùng chung
mutex reader_count_mutex; // Mutex để bảo vệ biến đếm số lượng độc giả
condition_variable cv; // Biến điều kiện để đồng bộ hóa luồng
int reader_count = 0; // Biến toàn cục để theo dõi số lượng độc giả hiện tại

void read(int reader_id) { // Hàm dành cho luồng độc giả
    {
        unique_lock<mutex> lock(reader_count_mutex); // Khóa mutex reader_count_mutex
        reader_count++; // Tăng số lượng độc giả
        if (reader_count == 1) {
            resource_mutex.lock(); // Nếu là độc giả đầu tiên, khóa mutex tài nguyên
        }
    }
    
    cout << "Độc giả " << reader_id << " đang đọc." << endl; // Xuất trạng thái đọc
    this_thread::sleep_for(chrono::milliseconds(100)); // Mô phỏng quá trình đọc

    {
        unique_lock<mutex> lock(reader_count_mutex); // Khóa lại mutex reader_count_mutex
        cout << "Độc giả " << reader_id << " đã đọc xong." << endl; // Xuất trạng thái hoàn thành đọc
        reader_count--; // Giảm số lượng độc giả
        if (reader_count == 0) {
            resource_mutex.unlock(); // Nếu là độc giả cuối cùng, mở khóa mutex tài nguyên
        }
    }
}

void write(int writer_id) { // Hàm dành cho luồng người ghi
    resource_mutex.lock(); // Khóa mutex tài nguyên
    cout << "Người ghi " << writer_id << " đang ghi." << endl; // Xuất trạng thái ghi
    this_thread::sleep_for(chrono::milliseconds(100)); // Mô phỏng quá trình ghi
    cout << "Người ghi " << writer_id << " đã ghi xong." << endl; // Xuất trạng thái hoàn thành ghi
    resource_mutex.unlock(); // Mở khóa mutex tài nguyên
}

int main() { // Hàm chính
    vector<thread> readers; // Vector để lưu trữ các luồng độc giả
    vector<thread> writers; // Vector để lưu trữ các luồng người ghi

    for (int i = 1; i <= 5; ++i) { // Vòng lặp tạo 5 luồng độc giả và 5 luồng người ghi
        readers.push_back(thread(read, i)); // Bắt đầu luồng độc giả
        writers.push_back(thread(write, i)); // Bắt đầu luồng người ghi
    }

    for (auto& t : readers) t.join(); // Chờ tất cả luồng độc giả hoàn thành
    for (auto& t : writers) t.join(); // Chờ tất cả luồng người ghi hoàn thành

    return 0; // Kết thúc chương trình
}

// author: Yu-Cheng (Morton) Kuo
// References: https://blog.jyotiprakash.org/readers-writers-problemz

