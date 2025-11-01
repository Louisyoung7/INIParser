#include "iniFile.h"

namespace louis {
namespace ini {
// 加载INI文件并将当前文件封装成类
bool IniFile::load(const string& fileName) {
    fileName_ = fileName;

    // 打开文件，准备读取
    std::ifstream fin(fileName_);
    if (fin.fail()) {
        return false;
    }

    // 读取文件
    string line;
    string section;
    while (std::getline(fin, line)) {
        if (line == "") {  // 空行
            continue;
        } else if (line[0] == '[') {  // 节
            int pos = line.find_first_of(']');
            section = trim(line.substr(1, pos - 1));
            // 存储当前节到section_中
            sections_[section] = pairs();
        } else {  // 键值对
            int pos = line.find_first_of('=');
            string option = trim(line.substr(0, pos));
            string value = trim(line.substr(pos + 1, line.length() - pos));
            sections_[section][option] = value;
        }
    }
    return true;
}

// 获取当前INI文件的某section的某option的value
value::Value& IniFile::get(const string& section, const string& option) {
    return sections_[section][option];
}

// 重载[]运算符用于获取和修改value
pairs& IniFile::operator[](const string& section) {
    return sections_[section];
}

// 添加或修改某option
void IniFile::set(const string& section, const string& option, const value::Value& value) {
    sections_[section][option] = value;
}

// 判断是否含有某section
bool IniFile::has(const string& section) {
    auto it = sections_.find(section);
    if (it != sections_.end()) {
        return true;
    }
    return false;
}

// 判断是否含有某option
bool IniFile::has(const string& section, const string& option) {
    if (!has(section)) {
        return false;
    }
    auto it = sections_[section].find(option);
    if (it != sections_[section].end()) {
        return true;
    }
    return false;
}

// 清空某option
void IniFile::remove(const string& section, const string& option) {
    if (!has(section, option)) {
        return;
    }
    sections_[section].erase(option);
}

// 清空某section
void IniFile::remove(const string& section) {
    sections_.erase(section);
}

// 清空INI文件
void IniFile::clear() {
    sections_.clear();
}

// 输出INI文件内容到字符串
string IniFile::str() {
    std::stringstream ss;
    for (auto pairs : sections_) {
        ss << "[" << pairs.first << "]" << std::endl;
        for (auto pair : pairs.second) {
            ss << pair.first << " = " << string(pair.second) << std::endl;
        }
        ss << std::endl;
    }
    return ss.str();
}

// 输出INI文件内容到屏幕
void IniFile::show() {
    std::cout << str() << std::endl;
}

// 将修改的内容保存到另一个文件
bool IniFile::save(const string& fileName) {
    std::ofstream fout(fileName);
    if (fout.fail()) {
        return false;
    }
    fout << str();
    fout.close();
    return true;
}

// 去除字符串首尾空格
string IniFile::trim(string str) {
    if (str.empty()) {
        return str;
    }
    str.erase(0, str.find_first_not_of(" \n\r"));
    str.erase(str.find_last_not_of(" \n\r") + 1);
    return str;
}
}  // namespace ini
}  // namespace louis
