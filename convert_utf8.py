import os

def batch_convert_to_utf8(directory):
    # 我们只转换这些后缀的文件，防止误伤其他文件
    target_extensions = ('.c', '.cpp', '.h', '.md', '.txt')
    converted_count = 0

    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(target_extensions):
                filepath = os.path.join(root, file)
                
                try:
                    # 第一步：先试着用 UTF-8 去读。如果没报错，说明它已经是 UTF-8，直接跳过
                    with open(filepath, 'r', encoding='utf-8') as f:
                        f.read()
                except UnicodeDecodeError:
                    # 第二步：如果报错了，说明它是 GBK（或 ANSI）等旧编码
                    try:
                        # 用 GBK 把内容读出来
                        with open(filepath, 'r', encoding='gbk') as f:
                            content = f.read()
                        
                        # 重新以纯正的 UTF-8 写回去
                        with open(filepath, 'w', encoding='utf-8') as f:
                            f.write(content)
                            
                        print(f"✅ 成功转换: {filepath}")
                        converted_count += 1
                    except Exception as e:
                        print(f"❌ 转换失败: {filepath}, 错误信息: {e}")

    print(f"\n🎉 批量转换完成！共转换了 {converted_count} 个文件。")

# 运行脚本，处理当前目录及其所有子目录
if __name__ == "__main__":
    batch_convert_to_utf8('.')