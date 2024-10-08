# CH552_LA_GachigumaRide

## 【概要】
ますたー様が開発したレジェンズアルセウスのガチグマライド（道具掘り）の自動化プログラムをCH552版に移植したものです。
- 【レジェンズアルセウス】ピートブロック・くろのきせきを自動収集【ガチグマライド】  
 <https://tangential-star.hatenablog.jp/entry/Arduino_pokemon_LegendsArceus01_finding_treasure_with_Ursaluna>

## 【必要なもの】
ハードウェア
- [CH552-MCU](https://booth.pm/ja/items/4372296)
- Ch552-MCUとNintendo Swicthを接続するUSBケーブル

ソフトウェア
- [Arduino IDE](https://www.arduino.cc/en/software)
- [WCHISPTool_Setup.zip](https://bzl-web.com/file/WCHISPTool_Setup.zip)
- 本プログラム

## 【使い方】
プログラムの基本動作はますたー様が開発したものと同じです。  
移植元の[記事](https://tangential-star.hatenablog.jp/entry/Arduino_pokemon_LegendsArceus01_finding_treasure_with_Ursaluna)を熟読願います。  
変更内容をまとめた小話(?)を[参考](#sanko)のURLに載せたので良かったら一読ください。

### ライブラリ、ch55xduinoのインストール
[CH55xSwitchControlのREADME](https://github.com/608/CH55xSwitchControl)を参考にしてください

### WCHISPToolのインストール
必要なもののURLからWCHISPTool_Setup.zipをダウンロードして解凍し、インストーラよりWCHISPToolをインストールしてください。

### ビルド
CH552_LA_GachigumaRide.inoをArduino IDEで開き、スケッチ→「コンパイル済みのバイナリをエクスポート」を実行します。  
成功すると同フォルダ内に.hexが生成されます。

### インストール
[ぼんじり様の記事](https://blog.bzl-web.com/entry/2022/11/24/001148)を参考にして、ビルドしたhexファイルをCH552-MCUに書き込んでください。

### 実行
以下の条件を全て満たした上で本プログラムを書き込んだCH552-MCUをSwitchに接続して下さい。
- 天冠の山麓内にいること
- 天冠の山麓の「山麓ベース」、「山中ベース」、「山頂ベース」が空を飛ぶで解放されていること
- ライドポケモンが「ガチグマ」になっていること
- 野生ポケモンに見つかっていないこと

<img src="https://github.com/user-attachments/assets/641927c6-0305-43de-b17a-41cc05662226" width=40% height=40%>
<img src="https://github.com/user-attachments/assets/9419ab61-352d-4708-8124-f89b4c766ff7" width=40% height=40%>

## 【使用実績】

クリア済みの日本語ROMで全５か所の発掘に成功しました。  
<img src="https://github.com/user-attachments/assets/c6ce3399-e765-41a9-82eb-e5ad426471a9" width=18% height=18%>
<img src="https://github.com/user-attachments/assets/a9e82290-28a4-4b91-960b-6a5d1ca90205" width=18% height=18%>
<img src="https://github.com/user-attachments/assets/b7cad8cf-6b1a-46e9-941e-ca0f846f8f55" width=18% height=18%>
<img src="https://github.com/user-attachments/assets/39830060-18c2-4fda-970d-88fd753f4115" width=18% height=18%>
<img src="https://github.com/user-attachments/assets/d8fdf950-ff4c-40a2-8439-acff4828575d" width=18% height=18%>

## 【Special Thanks】
- ますたー様  
  ベースプログラムの移植を許可頂き、ありがとうございます。
- ぼんじり様  
  CH552-MCUの販売、ありがとうございます。

## 【参考】
- ますたーの忘備録  
<https://tangential-star.hatenablog.jp/>

- ぼんじりちゃんねる公式ショップ  
<https://bzl.booth.pm/>

<div id="sanko">

- ポケモンSV CH552マイコンで三角関数をなんちゃらかんちゃらした話  
<https://note.com/our_holyland/n/n9ed7e0eb7ea1>
