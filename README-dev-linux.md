# Linux (Debian 10)

## 1 - Install bazel

### 1.1 - Manual installation

[Bazel Installation Instructions](https://docs.bazel.build/versions/master/install-windows.html).


### 1.2 - Step by step

```
sudo apt-get update
sudo apt-get install build-essential autoconf libtool pkg-config git curl -y
curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -
echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
sudo apt-get update
sudo apt-get install bazel -y
```

## 2 - Install SDL2

```
sudo apt-get install libsdl2-dev
```

## 3 - Building the project

```
bazel build //dash:dash_bin
```

## 4 - Running the project

```
bazel run //dash:dash_bin
```
