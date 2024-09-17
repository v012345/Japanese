#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <thread>

namespace fs = std::filesystem;

std::string getCurrentTimeAsString()
{
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 将时间点转换为 time_t 类型
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // 将 time_t 类型转换为 tm 结构体
    std::tm localTime = *std::localtime(&currentTime);

    // 格式化时间字符串
    std::stringstream ss;
    ss << std::put_time(&localTime, "%Y%m%d%H%M%S");
    return ss.str();
}

int main()
{
    // 文件路径
    fs::path filePath = "C:\\Users\\MH\\AppData\\Local\\Larian Studios\\Baldur's Gate 3\\PlayerProfiles\\Public\\Savegames\\Story\\5ac665e8-b77a-2fcb-2538-69a29f147aa6__HonourMode\\HonourMode.lsv";
    fs::path imagePath = "C:\\Users\\MH\\AppData\\Local\\Larian Studios\\Baldur's Gate 3\\PlayerProfiles\\Public\\Savegames\\Story\\5ac665e8-b77a-2fcb-2538-69a29f147aa6__HonourMode\\HonourMode.WebP";
    // fs::path filePath = "D:\\NightOwlZone\\Japanese\\tip.md";
    auto lastWriteTime1 = fs::last_write_time(filePath);
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // 获取文件的最后修改时间
        auto lastWriteTime2 = fs::last_write_time(filePath);
        if (lastWriteTime1 != lastWriteTime2)
        {
              std::this_thread::sleep_for(std::chrono::seconds(2));
            lastWriteTime1 = lastWriteTime2;
            // 将文件最后修改时间转换为时间点
            auto timePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lastWriteTime2);
            auto name = getCurrentTimeAsString();
            fs::path destinationFilePath = name + ".lsv";
            fs::path imagePathdestinationFilePath = name + ".WebP";
            fs::copy_file(filePath, destinationFilePath, fs::copy_options::overwrite_existing);
            fs::copy_file(imagePath, imagePathdestinationFilePath, fs::copy_options::overwrite_existing);
            std::cout << "copy file " << destinationFilePath << "\n";
            std::cout << "copy file " << imagePathdestinationFilePath << "\n";
        }
        else
        {
            std::cout << "do nothing~\n";
        }
    }

    return 0;
}