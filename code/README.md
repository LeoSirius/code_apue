# 代码使用说明

## 文件命名规则

按照`章节号_内容.c`的形式命名

## 注释与学习笔记

每个文件开头包含了一段注释，方便理解

## 环境搭建

apue的库下载好后

### 安装

```bash
sudo apt install libbsd-dev
cd apue.3e
# make
......

sudo cp ./include/apue.h /usr/include/
sudo cp ./lib/libapue.a /usr/local/lib/
```

注意在make前，确保systype.sh是可执行文件。

### 编译

```bash
gcc filename.c -lapue
```
