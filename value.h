#pragma once

#include <sstream>
#include <string>
using std::string;
using std::stringstream;

namespace louis {
namespace value {
// 以string类型为中介，将任意类型转换为Value，将Value转换为任意类型
class Value {
   public:
    Value() = default;
    // 基本数据类型转Value
    Value(int value);
    Value(double value);
    Value(const char* value);
    Value(const string& value);
    Value(bool value);

    // 重载赋值运算符
    Value& operator=(int value);
    Value& operator=(double value);
    Value& operator=(const char* value);
    Value& operator=(const string& value);
    Value& operator=(bool value);

    // Value转基本数据类型
    operator int() const;
    operator double() const;
    operator string() const;
    operator bool() const;

   private:
    string value_;
};
}  // namespace value
}  // namespace louis
