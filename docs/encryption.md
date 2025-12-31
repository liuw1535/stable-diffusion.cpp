# 图片加密功能使用说明

## 功能概述

stable-diffusion.cpp 现在支持在生成图片时自动加密，图片数据在内存中完成加密后再保存到硬盘，确保敏感图片的安全性。

## 使用方法

### 1. 生成加密图片

在运行 `sd-cli` 时添加 `--encrypt` 参数并设置密码：

```bash
./bin/sd-cli -m model.safetensors -p "a lovely cat" --encrypt mypassword
```

生成的图片将被加密保存，无法直接查看。

### 2. 解密图片

使用 `sd-decrypt` 工具解密图片：

```bash
./bin/sd-decrypt encrypted.png decrypted.png mypassword
```

参数说明：
- 第一个参数：加密的图片文件路径
- 第二个参数：解密后的输出文件路径
- 第三个参数：加密时使用的密码

### 3. 完整示例

```bash
# 生成加密图片
./bin/sd-cli -m ../models/v1-5-pruned-emaonly.safetensors \
  -p "a beautiful landscape" \
  -o encrypted_output.png \
  --encrypt secret123

# 解密图片查看
./bin/sd-decrypt encrypted_output.png decrypted_output.png secret123
```

## 注意事项

1. **密码安全**：请妥善保管加密密码，丢失密码将无法恢复图片
2. **加密算法**：使用基于XOR的对称加密，密码会生成256字节密钥
3. **性能影响**：加密过程在内存中完成，对性能影响极小
4. **文件格式**：支持PNG和JPG格式的加密
5. **批量生成**：使用 `--batch-count` 时，所有图片都会使用相同密码加密

## 编译

加密功能已集成到主程序中，按照正常流程编译即可：

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

编译完成后会生成：
- `sd-cli`：主程序（支持加密）
- `sd-decrypt`：解密工具

## 技术细节

- 加密在图片数据写入文件前在内存中完成
- 使用密码派生的256字节密钥进行XOR加密
- 加密是对称的，加密和解密使用相同的算法
- 不影响原有的图片生成流程和参数
- **后端兼容**：加密功能独立于计算后端，支持所有后端（CPU、CUDA、Vulkan、Metal、OpenCL、SYCL等）
