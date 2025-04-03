import threading
import time

class Philosopher(threading.Thread):
    def __init__(self, name, left_fork, right_fork):
        threading.Thread.__init__(self)
        self.name = name
        self.left_fork = left_fork
        self.right_fork = right_fork

    def run(self):
        while True:
            print(f"{self.name} đang suy nghĩ.")
            time.sleep(1)
            print(f"{self.name} đang đói.")
            self.dine()

    def dine(self):
        fork1, fork2 = self.left_fork, self.right_fork

        while True:
            fork1.acquire()  # Cố gắng lấy đũa bên trái
            acquired = fork2.acquire(False)  # Cố gắng lấy đũa bên phải mà không chặn
            if acquired:
                break  # Nếu lấy được cả hai đũa, thoát khỏi vòng lặp và bắt đầu ăn
            fork1.release()  # Nếu không lấy được đũa bên phải, nhả đũa trái và thử lại
            time.sleep(0.5)  # Tạm dừng ngắn trước khi thử lại

        print(f"{self.name} đang ăn.")
        time.sleep(2)  # Mô phỏng thời gian ăn
        fork1.release()
        fork2.release()
        print(f"{self.name} đã ăn xong.")

# Tạo khóa (Lock) cho từng chiếc đũa
forks = [threading.Lock() for _ in range(5)]

# Tạo các triết gia
philosophers = [
    Philosopher(f"Triết gia {i + 1}", forks[i % 5], forks[(i + 1) % 5])
    for i in range(5)
]

# Bắt đầu các luồng (thread) của triết gia
for philosopher in philosophers:
    philosopher.start()

# author: Brandon Kindred
# References: https://brandonkindred.medium.com/mastering-concurrency-with-the-dining-philosopher-problem-8445920f7863