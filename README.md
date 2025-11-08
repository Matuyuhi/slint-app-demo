# Dashboard App - Slint + C++

モダンなデザインのリアルタイムダッシュボードアプリケーション

## 特徴

- **リアルタイムメトリクス表示**: CPU、メモリ、ディスク、ネットワーク使用率をリアルタイムで表示
- **パフォーマンスグラフ**: アニメーション付きのグラフでシステムパフォーマンスを可視化
- **システムステータス**: 各種サービスの稼働状態を監視
- **モダンなUI**: ダークテーマとスムーズなアニメーションで洗練されたデザイン

## 技術スタック

- **Slint**: UIフレームワーク（宣言的UI）
- **C++20**: バックエンドロジック
- **CMake**: ビルドシステム

## 必要な環境

- CMake 3.21以上
- C++20対応のコンパイラ（GCC 10+, Clang 12+, MSVC 2019+）
- **Rust** (Slintのビルドに必要)

### Rustのインストール

**Linux/macOS:**
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source $HOME/.cargo/env
```

**Ubuntu/Debian:**
```bash
sudo apt-get install rustc cargo
```

**Windows:**
[rustup-init.exe](https://rustup.rs/)をダウンロードして実行

## ビルド方法

```bash
# Rustがインストールされていることを確認
rustc --version

# ビルドディレクトリを作成
mkdir build
cd build

# CMakeを実行（初回はSlintのダウンロードとビルドに時間がかかります）
cmake ..

# ビルド
cmake --build .

# 実行
./dashboard-app
```

## プロジェクト構造

```
slint-app-demo/
├── ui/
│   └── appwindow.slint    # UIデザイン（Slint言語）
├── src/
│   └── main.cpp           # C++メインファイル
├── CMakeLists.txt         # ビルド設定
└── README.md
```

## UIコンポーネント

### MetricCard
各メトリクスを表示するカードコンポーネント。プログレスバーとアニメーション付き。

### GraphBar
パフォーマンスグラフの各バー。値の変化をスムーズにアニメーション。

### StatusIndicator
システムサービスの稼働状態を色で表示。

## データ更新

タイマーを使用して1秒ごとにメトリクスを更新：
- CPUとメモリ使用率は滑らかに変化
- グラフは波形パターンで推移
- ステータスインジケーターはランダムに変化

## カスタマイズ

`src/main.cpp`で更新頻度やデータの範囲を調整できます。
`ui/appwindow.slint`でUIのデザインやカラースキームを変更できます。
