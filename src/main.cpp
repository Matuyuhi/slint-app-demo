#include "appwindow.h"
#include <random>
#include <cmath>

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

    // グラフの初期値
    ui->set_graph1(45.0);
    ui->set_graph2(72.0);
    ui->set_graph3(38.0);
    ui->set_graph4(91.0);
    ui->set_graph5(56.0);
    ui->set_graph6(84.0);
    ui->set_graph7(63.0);
    ui->set_graph8(77.0);

    // タイマーでデータを更新（1秒ごと）
    auto timer = slint::Timer();
    timer.start(slint::TimerMode::Repeated, std::chrono::seconds(1), [&]() {
        // CPUとメモリのスムーズな変化
        static float cpu_target = 65.0f;
        static float mem_target = 58.0f;
        static float current_cpu = 65.0f;
        static float current_mem = 58.0f;
        static int update_counter = 0;

        update_counter++;

        // 5秒ごとに新しいターゲット値を設定
        if (update_counter % 5 == 0) {
            cpu_target = cpu_dist(gen);
            mem_target = mem_dist(gen);
        }

        // スムーズに値を変化させる
        current_cpu += (cpu_target - current_cpu) * 0.2f;
        current_mem += (mem_target - current_mem) * 0.2f;

        ui->set_cpu_usage(static_cast<int>(current_cpu));
        ui->set_memory_usage(static_cast<int>(current_mem));
        ui->set_disk_usage(disk_dist(gen));
        ui->set_network_usage(net_dist(gen));

        // グラフデータを波のように更新
        static float phase = 0.0f;
        phase += 0.3f;

        ui->set_graph1(50.0f + 30.0f * std::sin(phase));
        ui->set_graph2(60.0f + 25.0f * std::sin(phase + 0.5));
        ui->set_graph3(45.0f + 35.0f * std::sin(phase + 1.0));
        ui->set_graph4(70.0f + 20.0f * std::sin(phase + 1.5));
        ui->set_graph5(55.0f + 30.0f * std::sin(phase + 2.0));
        ui->set_graph6(65.0f + 25.0f * std::sin(phase + 2.5));
        ui->set_graph7(50.0f + 35.0f * std::sin(phase + 3.0));
        ui->set_graph8(60.0f + 30.0f * std::sin(phase + 3.5));

        // ランダムにステータスを変更（たまにfalseにする）
        if (update_counter % 20 == 0) {
            ui->set_system_status(gen() % 10 != 0);
            ui->set_database_status(gen() % 10 != 0);
            ui->set_api_status(gen() % 10 != 0);
        }
    });

    ui->run();

    return 0;
}
