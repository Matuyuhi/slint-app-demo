#include "appwindow.h"
#include <random>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <sstream>

// 現在時刻を取得する関数
std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
    return ss.str();
}

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    // 乱数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> cpu_dist(30, 95);
    std::uniform_int_distribution<> mem_dist(40, 85);
    std::uniform_int_distribution<> disk_dist(50, 75);
    std::uniform_int_distribution<> net_dist(5, 95);
    std::uniform_real_distribution<> graph_dist(20.0, 95.0);

    // 初期値設定
    ui->set_cpu_usage(65);
    ui->set_memory_usage(58);
    ui->set_disk_usage(62);
    ui->set_network_usage(42);
    ui->set_system_status(true);
    ui->set_database_status(true);
    ui->set_api_status(true);
    ui->set_current_time(slint::SharedString(get_current_time()));

    // グラフの初期値
    ui->set_graph1(45.0);
    ui->set_graph2(72.0);
    ui->set_graph3(38.0);
    ui->set_graph4(91.0);
    ui->set_graph5(56.0);
    ui->set_graph6(84.0);
    ui->set_graph7(63.0);
    ui->set_graph8(77.0);

    // ハイフレームレートタイマーでデータを更新（500msごと）
    auto timer = slint::Timer();
    timer.start(slint::TimerMode::Repeated, std::chrono::milliseconds(500), [&]() {
        // CPUとメモリのスムーズな変化
        static float cpu_target = 65.0f;
        static float mem_target = 58.0f;
        static float disk_target = 62.0f;
        static float current_cpu = 65.0f;
        static float current_mem = 58.0f;
        static float current_disk = 62.0f;
        static int update_counter = 0;

        update_counter++;

        // 現在時刻を更新
        ui->set_current_time(slint::SharedString(get_current_time()));

        // 10回（5秒）ごとに新しいターゲット値を設定
        if (update_counter % 10 == 0) {
            cpu_target = cpu_dist(gen);
            mem_target = mem_dist(gen);
            disk_target = disk_dist(gen);
        }

        // スムーズに値を変化させる（イージング）
        current_cpu += (cpu_target - current_cpu) * 0.15f;
        current_mem += (mem_target - current_mem) * 0.15f;
        current_disk += (disk_target - current_disk) * 0.08f;

        ui->set_cpu_usage(static_cast<int>(current_cpu));
        ui->set_memory_usage(static_cast<int>(current_mem));
        ui->set_disk_usage(static_cast<int>(current_disk));
        ui->set_network_usage(net_dist(gen));

        // グラフデータを美しい波のように更新
        static float phase = 0.0f;
        phase += 0.15f;  // スムーズなアニメーション

        // 複雑な波形を作成（複数の正弦波を組み合わせ）
        ui->set_graph1(55.0f + 25.0f * std::sin(phase) + 10.0f * std::sin(phase * 2.3));
        ui->set_graph2(60.0f + 20.0f * std::sin(phase + 0.5) + 8.0f * std::cos(phase * 1.7));
        ui->set_graph3(50.0f + 30.0f * std::sin(phase + 1.0) + 5.0f * std::sin(phase * 3.1));
        ui->set_graph4(70.0f + 18.0f * std::sin(phase + 1.5) + 7.0f * std::cos(phase * 2.5));
        ui->set_graph5(58.0f + 28.0f * std::sin(phase + 2.0) + 9.0f * std::sin(phase * 1.9));
        ui->set_graph6(65.0f + 22.0f * std::sin(phase + 2.5) + 6.0f * std::cos(phase * 2.8));
        ui->set_graph7(52.0f + 32.0f * std::sin(phase + 3.0) + 8.0f * std::sin(phase * 2.2));
        ui->set_graph8(62.0f + 26.0f * std::sin(phase + 3.5) + 10.0f * std::cos(phase * 1.5));

        // ランダムにステータスを変更（たまにfalseにする）
        if (update_counter % 40 == 0) {  // 20秒ごと
            ui->set_system_status(gen() % 10 != 0);
            ui->set_database_status(gen() % 10 != 0);
            ui->set_api_status(gen() % 10 != 0);
        }
    });

    ui->run();

    return 0;
}
