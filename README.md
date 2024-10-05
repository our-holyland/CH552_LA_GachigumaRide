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
変更内容をまとめた小話(?)は[参考](#sanko)にURLを載せたので良かったら一読ください。

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
以下の条件を全て満たした上で天冠の山麓で本プログラムを書き込んだCH552-MCUをSwitchに接続して下さい。
- 天冠の山麓の「山麓ベース」、「山中ベース」、「山頂ベース」が空を飛ぶで解放されていること
- ライドポケモンのカーソルが「ガチグマ」になっていること
- 野生ポケモンに見つかっていないこと

<p align="center">
  <img src="https://github.com/user-attachments/assets/074046e6-b8c3-4594-b63b-72049dbf3534" width=30% height=30%>
</p>

## 【使用実績】
クリア済みの日本語ROMで全５か所の発掘に成功しました。  
<img src="https://github.com/user-attachments/assets/4259774f-6be1-45fb-b87d-16c59077cd68" width=20% height=20%>
<img src="https://github.com/user-attachments/assets/5b54a3e2-54d9-43ae-9ac2-fc28d049db9f" width=20% height=20%>
<img src="https://github.com/user-attachments/assets/61e1c6dd-911f-4a46-b9c3-8e0327e1a6af" width=20% height=20%>
<img src="https://github.com/user-attachments/assets/947d8bb9-d3c2-4f7d-87d0-cc16a97d0383" width=20% height=20%>
<img src="https://github.com/user-attachments/assets/15710cd7-deee-43f4-a0ed-2e2155f470a7" width=20% height=20%>

## 【参考】

- ますたーの忘備録  
　<https://tangential-star.hatenablog.jp/>

- ぼんじりちゃんねる公式ショップ  
　<https://bzl.booth.pm/>

<div id="sanko">

- ポケモンSV CH552マイコンで三角関数をなんちゃらかんちゃらした話  
  <https://note.com/our_holyland/n/n9ed7e0eb7ea1>
