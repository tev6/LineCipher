# LineCipher - 文字线条化展示工具
![](https://img.shields.io/badge/License-MIT-yellow.svg)
![](https://img.shields.io/badge/C++-17-blue.svg)

一个创新的C++程序，将普通文本转换为独特的线条图案，可以在纸上清晰展示和识别。

## ✨ 项目特色
- 视觉趣味：将文本转换为易于绘制的线条图案
- 双向转换：支持文本到线条的编码和线条到文本的解码
- 易于扩展：代码结构清晰，易于添加新功能
- 易于使用：简单的命令行交互界面

## 🚀 快速开始
- C++编译器 (支持C++11或更高版本)
- 标准模板库 (STL)

### 编译运行
```bash
# 克隆项目
git clone https://github.com/tev6/LineCipher.git
cd LineCipher

# 编译程序
g++ -o linecipher main.cpp -std=c++11

# 运行程序
./linecipher
```

### 三种语言调用/测试

#### 1) C++（库调用）
项目提供可复用头文件 [linecipher.h](file:///z:/LineCipher/linecipher.h)，包含初始化、编码、解码接口：

```cpp
#include <iostream>
#include <sstream>
#include <string>
#include "linecipher.h"

int main() {
    linecipher::init();
    std::string text = "hello!";
    std::string encoded = linecipher::encode(text);
    std::cout << encoded << std::endl;

    std::istringstream iss(encoded);
    std::string top, mid, bot;
    std::getline(iss, top);
    std::getline(iss, mid);
    std::getline(iss, bot);
    std::cout << linecipher::decode(top, mid, bot) << std::endl;
}
```

示例程序：[test.cpp](file:///z:/LineCipher/test.cpp)

#### 2) Python（库调用）
提供纯 Python 实现：[linecipher.py](file:///z:/LineCipher/linecipher.py)

```bash
python test.py
```

示例程序：[test.py](file:///z:/LineCipher/test.py)

#### 3) HTML + JavaScript（单文件网页）
打开 [linecipher.html](file:///z:/LineCipher/linecipher.html)，页面中间卡片式输入框，选择“编码/解码”后点击运行即可。

如果需要本地预览服务器（可选）：
```bash
python -m http.server 8000
```
## 📖 使用方法
程序提供两种操作模式：


1. 文本转线条模式
输入文本字符串，程序会生成对应的三行线条图案：

```text
输入: hello! my name is josh! nice to meet you!

输出:
         _    _    _       _                                                    _                _              _           _                           _            _ |
/\   /\ / \_ / \_ / \    _/ \ _    _ _  /\ _ _   /\_    _ /\ _ _/\   _ _    /\ / \   _ /\      _/ \ _ _   _/\ _/ \ /\ _    / \ _    _ /\ /\    _ _  /\ / \   /\    _/ \|
  \/|  |    |    |   |\_/    | |\_/ | \/  | | \/|   |\_/ |  | |   |\/ | |\_/  |   |\/ |  \/|\_/    | | \/|   |    |  | |\/|   | |\_/ |  |  |\/| | \/  |   |\/  |\_/    |
```
2. 线条转文本模式
输入三行线条图案，程序会解码为原始文本。

## 🔍 工作原理
字符编码系统
程序使用7种基本线条元素组合来表示字符：

- / - 向上的斜线
- \ - 向下的斜线
- _ - 直线
- | - 字符和字符串的终止符号

### 编码算法
1. 为每个字符生成唯一的数字序列（1-7）
2. 将数字序列映射到三行线条图案
3. 确保每个字符的线条图案都是唯一且可区分的

### 支持字符集
程序支持以下常见的字符：字母、数字、常用标点符号

```text
 e t a o i n s r h l c d u m f p w g b y v k x j q z 1 2 3 4 5 6 7 8 9 0 , . / > @ ( ) !
```
## 📁 项目结构
```text
LineCipher/
├── main.cpp
├── linecipher.h
├── test.cpp
├── linecipher.py
├── test.py
├── linecipher.html
├── README.md
```
## 💡 使用场景
- 创意艺术：将文字以艺术线条形式展示
- 趣味项目：独特的文字展示方式

## 📄 许可证
本项目采用MIT许可证 - 详见LICENSE文件
