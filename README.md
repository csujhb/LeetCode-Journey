
---


# LeetCode-Journey | 算法与工程化实践记录

[![Language](https://img.shields.io/badge/Language-C%2B%2B%2FC-blue.svg)](https://en.cppreference.com/)
[![Build](https://img.shields.io/badge/Build-CMake-brightgreen.svg)](https://cmake.org/)
[![Encoding](https://img.shields.io/badge/Encoding-UTF--8-orange.svg)](#)

本项目用于记录我的力扣（LeetCode）刷题历程与算法思路。
This repository contains my LeetCode solutions, algorithm analysis, and engineering practices.

---

## 🌟 项目亮点 | Highlights

* **工程化构建 (Engineering-Driven)**: 
    使用 **CMake** 自动化构建系统，支持递归扫描子目录，一键生成 Visual Studio 工程，方便进行本地调试与语法检查。
* **模块化设计 (Modular Structure)**: 
    每道题目均拥有独立文件夹，包含：
    - `*.c / *.cpp`: 核心算法实现。
    - `notes.md`: 题目解析、复杂度分析的内存优化思考。

---

## 📂 目录结构 | Directory Structure

```text
.
├── CMakeLists.txt        # 核心构建脚本 (Core Build Script)
├── .gitignore            # Git 忽略配置 (Build artifacts excluded)
├── README.md             # 本说明文档
├── 01_Two_Sum/           # 题目文件夹案例
│   ├── main.c            # 源码实现
│   └── notes.md          # 解题笔记 (Notes & Analysis)
└── ...
```

---

## 🛠️ 本地构建与运行 | Build Instructions

项目推荐在 **Windows + VS Code + MSVC** 环境下运行。

1.  **克隆仓库 (Clone)**:
    ```bash
    git clone [https://github.com/csujhb/LeetCode-Journey.git](https://github.com/eryao021128/LeetCode-Journey.git)
    cd LeetCode-Journey
    ```

2.  **配置并编译 (Configure & Build)**:
    使用 VS Code 的 **CMake Tools** 插件，或在终端执行：
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

3.  **编码说明 (Encoding)**:
    若在 Windows 下遇到注释乱码，请确保编辑器以 **UTF-8** 编码打开文件。

---

## 📝 刷题进度 | Roadmap

| # | 题目 (Problem) | 难度 (Diff) | 知识点 (Tags) | 状态 (Status) |
| :--- | :--- | :--- | :--- | :--- |
| 01 | [两数之和](./01_Two_Sum/) | Easy | Hash Table | ✅ 已完成 |
| 206 | [反转链表](./206_Reverse_List/) | Easy | Pointers | ✅ 已完成 |
| 15 | [三数之和](./15_3Sum/) | Medium | Two Pointers | 🚧 进行中 |

---

## 📧 联系与支持 | Contact

* **Author**:csujhb
* **Focus**: Embedded Systems
* **GitHub**: [csujhb](https://github.com/csujhb)

---
*Created with ❤️ by csujhb. Happy Coding!*
