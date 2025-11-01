#pragma once

#include <fstream>
#include <iostream>
#include <map>

#include "value.h"

namespace louis {
namespace ini {
// Section中每个键值对的别名
using pairs = std::map<string, value::Value>;
class IniFile {
   public:
    IniFile() = default;

    // 加载INI文件并将当前文件封装成类
    bool load(const string& fileName);

    // 获取当前INI文件某option的value
    value::Value& get(const string& section, const string& option);

    // 重载[]运算符用于获取和修改value
    pairs& operator[](const string& section);

    // 添加或修改某option
    void set(const string& section, const string& option, const value::Value& value);

    // 判断是否含有某section
    bool has(const string& section);

    // 判断是否含有某option
    bool has(const string& section, const string& option);

    // 清空某option
    void remove(const string& section, const string& option);

    // 清空某section
    void remove(const string& section);

    // 清空INI文件
    void clear();

    // 输出INI文件内容到字符串
    string str();

    // 输出INI文件内容到屏幕
    void show();

    // 将修改的内容保存到另一个文件
    bool save(const string& fileName);

   private:
    // 去除字符串首尾空格
    string trim(string str);

   private:
    string fileName_;
    std::map<string, pairs> sections_;
};

}  // namespace ini
}  // namespace louis
