## 「３」と「３の倍数」でピッチシフトが発生する　OpenJtalk

「３」と「３の倍数」でを検知した際に、自動的にピッチを跳ね上げて読み上げる改造版 Open JTalk です。

## 概要
通常の Open JTalk　にC言語で処理を追加し、特定の条件下で音声合成エンジン（hts_engine）のピッチパラメータを動的に変更するように改造しています。

## ライセンス
本プログラムはOpenJtalkのライセンスであるBSDライセンスに準じます。

## 動作環境　Windows　/ macOS 対応
必要ツール
⭐︎Windows
```bash
sudo apt update
sudo apt install build-essential automake autoconf libtool
```

⭐︎macOS
```bash
brew install automake autoconf libtool
```

## ビルド方法

1.土台の「hts_engine_API」のビルド
```bash
cd hts_engine_API-1.10
chmod +x ./configure
./configure
make
```

2.OpenJtalk本体のビルド
⭐︎Windowsの場合
```bash
cd ../open_jtalk-1.11
chmod +x ./configure
./configure \
--with-hts-engine-header-path=../hts_engine_API-1.10/include \
--with-hts-engine-library-path=../hts_engine_API-1.10/lib
make
```

⭐︎macOSの場合
```bash
cd ../open_jtalk-1.11
chmod +x ./configure
./configure LIBS="-liconv" \
--with-hts-engine-header-path=../hts_engine_API-1.10/include \
--with-hts-engine-library-path=../hts_engine_API-1.10/lib
make
```

3.実行方法
ビルド完了後、リポジトリのルートディレクトリで以下のコマンドを実行してください。
※ fish シェルや zsh での改行エラーを防ぐため、1行にまとめて記述しています。
下は「1、2、3、4、5、6、7、8、9、10」を読み上げるコマンドです。

```bash
echo "1、2、3、4、5、6、7、8、9、10" | ./open_jtalk-1.11/bin/open_jtalk -x ./dict -m ./voice/nitech_jp_atr503_m001.htsvoice -ow output.wav -r 0.7 -fm 2.0 -a 0.55
```

ここまでで「３」と「３の倍数」でピッチシフトが発生する　OpenJtalkのビルドは終了です。
話す速度や音声全体のピッチの指定、音量の指定については補足に記載しています。

## ディレクトリ構成
・open_jtalk-1.11/: 改造済みソースコード本体
・hts_engine_API-1.10/: 音声合成エンジンライブラリ
・dict/: 辞書ファイル (UTF-8)
・voice/: HTS Voice モデルファイル

＝＝＝＝＝＝＝＝＝＝＝＝
⭐︎補足
Open JTalkを実行する際は、通常以下の3つのオプション指定が必要です。

1.  **`-x`**: 辞書ディレクトリのパス
2.  **`-m`**: 音響モデル（.htsvoice）のパス
3.  **`-ow`**: 出力する音声ファイル（.wav）の名前

## 使用例
⭐︎⭐︎以下のコマンドを使用する際はパスの指定に気をつけてください。
### 1. 基本的な音声生成

テキストファイル `input.txt` を読み込み、音声 `output.wav` を生成する場合。

```bash
open_jtalk \
  -x /path/to/dic_dir \
  -m /path/to/voice.htsvoice \
  -ow output.wav \
  input.txt
```

### 2. コマンドラインから直接テキストを入力

`echo` コマンドを使ってテキストを渡す場合。

```bash
echo "こんにちは" | open_jtalk \
  -x /path/to/dic_dir \
  -m /path/to/voice.htsvoice \
  -ow output.wav
```

### 3\. 声の調整（速度・高さ・音量）

  - 話速を速くする (`-r 1.2`)
  - 声を少し高くする (`-fm 2.0`)
  - 音量を上げる (`-g 5.0`)

<!-- end list -->

```bash
open_jtalk \
  -x /path/to/dic_dir \
  -m /path/to/voice.htsvoice \
  -ow output.wav \
  -r 1.2 \
  -fm 2.0 \
  -g 5.0 \
  input.txt
```

## オプション一覧
⭐︎⭐︎以下のオプションを使用することで多様な読み上げ音声を生成することもできます。

| オプション | 引数 | 説明 | デフォルト値 | 設定可能範囲 |
| :--- | :---: | :--- | :---: | :---: |
| **`-x`** | `dir` | **【重要】** 辞書ディレクトリの指定 | N/A | - |
| **`-m`** | `file` | **【重要】** HTSボイスファイル(.htsvoice)の指定 -> 話者 | N/A | - |
| **`-ow`** | `file` | **【重要】** 生成される音声ファイル(.wav)の出力先 | N/A | - |
| **`-ot`** | `file` | トレース情報の出力ファイル | N/A | - |
| **`-s`** | `int` | サンプリング周波数 (Hz) | auto | 1以上 |
| **`-p`** | `int` | フレーム周期 (point) | auto | 1以上 |
| **`-a`** | `float` | オールパス定数 -> 声質 | auto | 0.0 - 1.0 |
| **`-b`** | `float` | ポストフィルタ係数 | 0.0 | 0.0 - 1.0 |
| **`-r`** | `float` | **話速** (読み上げスピード) -> 話速 | 1.0 | 0.0以上 |
| **`-fm`** | `float` | **追加ハーフトーン** (声の高さ調整) ->ピッチシフト | 0.0 | - |
| **`-u`** | `float` | 有声/無声の閾値 | 0.5 | 0.0 - 1.0 |
| **`-jm`** | `float` | スペクトラム系列内変動の重み | 1.0 | 0.0以上 |
| **`-jf`** | `float` | F0系列内変動の重み | 1.0 | 0.0以上 |
| **`-g`** | `float` | **音量** (dB) | 0.0 | - |
| **`-z`** | `int` | オーディオバッファサイズ (0でオフ) | 0 | 0以上 |

