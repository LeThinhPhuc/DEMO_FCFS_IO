#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <conio.h>
#include <iomanip> 
using namespace std;

struct process {
    int id; // ID của tiến trình
    int arrival_time; // Thời gian đến của tiến trình
    int cpu_burst_time; // Thời gian chạy CPU của tiến trình
    int io_start_time; // Thời gian bắt đầu I/O của tiến trình
    int io_burst_time; // Thời gian I/O của tiến trình
    int waitTime;         // Thời gian chờ
    int turnaroundTime;   // Thời gian xoay vòng
public:

};
istream& operator >> (istream& in, process& a)
{
    in >> a.id >> a.arrival_time >> a.cpu_burst_time >> a.io_start_time >> a.io_burst_time;
    return in;

}
bool compare_arrival_time(process a, process b) {
    return a.arrival_time < b.arrival_time;
}


void fcfs_with_io(vector<process> processes) {
    queue<process> ready_queue; // Hàng đợi sẵn sàng
    int current_time = 0; // Thời gian hiện tại

    // Sắp xếp các tiến trình theo thời gian đến
    sort(processes.begin(), processes.end(), compare_arrival_time);

    // Thực hiện lập lịch cho từng tiến trình
    for (int i = 0; i < processes.size(); i++) {
        process p = processes[i];

        // Kiểm tra xem tiến trình đã đến chưa
        if (p.arrival_time > current_time) {
            current_time = p.arrival_time;
        }

        // Thực hiện I/O nếu cần
        if (p.io_start_time <= current_time) {
            current_time += p.io_burst_time;
        }

        // Thực hiện chạy CPU
        current_time += p.cpu_burst_time;

        // Thêm tiến trình vào hàng đợi sẵn sàng
        while (!ready_queue.empty() && ready_queue.front().arrival_time <= current_time) {
            process q = ready_queue.front();
            ready_queue.pop();
            fcfs_with_io({ q }); // Gọi đệ quy với vector chứa một tiến trình
        }

        // Thêm tiến trình vào hàng đợi sẵn sàng
        ready_queue.push(p);
    }

    // Thực hiện lập lịch cho các tiến trình còn lại trong hàng đợi sẵn sàng
    while (!ready_queue.empty()) {
        process p = ready_queue.front();
        ready_queue.pop();

        // Kiểm tra xem tiến trình đã đến chưa
        if (p.arrival_time > current_time) {
            current_time = p.arrival_time;
        }

        // Thực hiện I/O nếu cần
        if (p.io_start_time <= current_time) {
            current_time += p.io_burst_time;
        }

        // Thực hiện chạy CPU
        current_time += p.cpu_burst_time;
    }
}
void calculateTimes(vector<process>& processes) {
    int currentTime = 0;

    for (int i = 0; i < processes.size(); i++) {
        process& currentProcess = processes[i];

        // Thời gian chờ của tiến trình là thời gian từ khi tiến trình đến cho đến khi nó được thực thi
        currentProcess.waitTime = currentTime - currentProcess.arrival_time;

        // Nếu thời gian chờ âm, tiến trình chưa đến. Cập nhật thời gian chờ là 0.
        if (currentProcess.waitTime < 0) {
            currentProcess.waitTime = 0;
            currentTime = currentProcess.arrival_time;
        }

        // Cập nhật thời gian bắt đầu I/O nếu cần
        if (currentProcess.io_start_time > currentTime) {
            currentTime = currentProcess.io_start_time;
        }

        // Thời gian chạy CPU
        currentTime += currentProcess.cpu_burst_time;

        // Thời gian xoay vòng của tiến trình là tổng thời gian chạy CPU và I/O
        currentProcess.turnaroundTime = currentTime - currentProcess.arrival_time;

        // Cập nhật thời gian kết thúc I/O của tiến trình tiếp theo
        if (i < processes.size() - 1) {
            process& nextProcess = processes[i + 1];
            nextProcess.io_start_time = currentTime;
        }
    }
}


int main() {
    cout << "\t\t\t\t\t\t\t************************************************" << endl;
    cout << "\t\t\t\t\t\t\t*** \x1b[33mCHUONG TRINH MO PHONG THUAT TOAN FCFS IO\x1b[0m ***" << endl;
    cout << "\t\t\t\t\t\t\t************************************************" << endl;
    /*  vector<process> processes = {
          {1, 0, 10, 5, 2},
          {2, 1, 5, 0, 3},
          {3, 2, 8, 4, 1},
          {4, 3, 2, 2, 2},
          {5, 4, 4, 3, 3},
      };*/
    vector<process> processes;
    int n;
    cout << "\t \x1b[33mNhap so tien trinh\x1b[0m : "; cin >> n;
    for (int i = 0; i < n; i++) {
        process tmp;
        cout << "\t\t\x1b[33mNhap tien trinh thu\x1b[0m " << "\x1b[33m" << i + 1 << "\x1b[0m"<< endl;
        cout << "\t\t\t ID : "; cin >> tmp.id;
        cout << "\t\t\tArrival Time : "; cin >> tmp.arrival_time;
        cout << "\t\t\tCPU Burst Time : "; cin >> tmp.cpu_burst_time;
        cout << "\t\t\tIO Start Time : "; cin >> tmp.io_start_time;
        cout << "\t\t\tIO Burst Time : "; cin >> tmp.io_burst_time;
        processes.push_back(tmp);
    }
    cout << endl;
    cout << "\t\t\t" << setw(75) << "\x1b[33mBANG THONG KE CAC TIEN TRINH\x1b[0m" << endl;
    cout << "\t\t\t+----+---------------+---------------+---------------+----------------+----------------+--------------+\n";
    cout << "\t\t\t| \x1b[33mID\x1b[0m | \x1b[33mArrival Time\x1b[0m | \x1b[33mCPU Burst Time\x1b[0m | \x1b[33mI/O Start Time\x1b[0m| \x1b[33mI/O Burst Time\x1b[0m | \x1b[33mTime turnaround\x1b[0m| \x1b[33mTime waiting\x1b[0m |\n";
    fcfs_with_io(processes);
    calculateTimes(processes);
    // In thông tin về tiến trình
    cout << "\t\t\t+----+---------------+---------------+---------------+----------------+----------------+--------------+\n";
    for (int i = 0; i < processes.size(); i++) {
        process p = processes[i];
        cout << "\t\t\t| " << setw(2) << p.id << " | " << setw(13) << p.arrival_time << " | " << setw(13) << p.cpu_burst_time << " | " << setw(13) << p.io_start_time << " | " << setw(14) << p.io_burst_time << " | " << setw(14) << p.turnaroundTime << " | " << setw(12) << p.waitTime << " |" << endl;
        cout << "\t\t\t+----+---------------+---------------+---------------+----------------+----------------+--------------+\n";

    }
    //cout << "\t\t\t+----+---------------+---------------+---------------+----------------+----------------+--------------+\n";
    int sumWait = 0;
    int sumTurn = 0;
   
        cout << "\n\t\t\x1b[33mThoi gian xoay vong trung binh\x1b[0m : ";

    for (int i = 0; i < processes.size(); i++) {
        sumTurn += processes[i].turnaroundTime;
        if (i == 0) {
            cout << processes[i].turnaroundTime;
        }
        else
            cout << " + " << processes[i].turnaroundTime;
    }
    cout << " / " << processes.size() << " = " << setprecision(2) << fixed << sumTurn / static_cast<double>(processes.size()) << endl;
   
        cout << "\t\t\x1b[33mThoi gian cho trung binh\x1b[0m : ";

    for (int i = 0; i < processes.size(); i++) {
        sumWait += processes[i].waitTime;
        if (i == 0) {
            cout << processes[i].waitTime;
        }
        else
            cout << " + " << processes[i].waitTime;
    }
    cout << " / " << processes.size() << " = " << setprecision(2) << fixed << sumWait / static_cast<double>(processes.size()) << endl;



    return 0;
}
