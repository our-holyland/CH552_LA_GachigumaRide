/* 
 *  ★ポケモンレジェンズアルセウス　ガチグマライドで色々掘ろう＠天冠の山麓 山頂ベース★
 *  天冠の山麓の山頂ベースでArduinoを挿すとスタート。
 *  ライドポケモンは、「ガチグマ」にカーソルがあっている状態で使うこと！（重要）
 *  
 * 
 * 実測値で、12時間放置で242ループ。下記が手に入りました。
 * ・ピートブロック：13個
 * ・クスリソウ：242個
 * ・ごりごりミネラル：404個
 * ・スイートトリュフ：81個
 * ・どろだんご：260個
 * ・ほしのかけら：20個
 * ・つきのいし：12個
 * ・そらいろたまいし：200個
 * ・たいようのいし：7個
 * ・くろのきせき：9個
 *  
 *  設定
 *  ・はなしのはやさ：はやい
 *  
 *  (c) 2022 ますたーの忘備録
 *  https://tangential-star.hatenablog.jp/
*/

#include <SwitchControlLibrary.h>

#define HOLDTIME (95)     // 1回のキー入力の長押し時間

// ★修正ここから★-----------------

// 【天冠の山麓】マップでXを押したときに「山頂ベース」が上から何番目か？（山麓ベース=0・山中=1・山頂=2・迎月の戦場=3・やめる）
const int SANROKU = 0; // 山麓ベース
const int SANCHU  = 1; // 山中ベース
const int SANCHO  = 2; // 山頂ベース
const int GEIGETSU= 3; // 迎月の戦場

// 【コトブキムラ】マップでXを押したときに「表門前」が何番目か？
const int HOMBU    = 0; // 本部前
const int OMOTEMON = 1; // 表門前
const int YAGAI    = 2; // 野外訓練場
const int NOUJO    = 3; // 農場前 
const int KUNRENJO = 4; // 訓練場前

// 【入り口】マップでカーソルを外してから「↓」キーで「天冠の山麓」が何番目か？
const int KOTOBUKI = 1; // コトブキムラ
const int KOKUYO   = 2; // 黒曜の原野
const int GUREN    = 3; // 紅蓮の湿地
const int GUNJO    = 4; // 群青の海岸
const int TENGAN   = 5; // 天冠の山麓
const int JUMPAKU  = 6; // 純白の糖度
const int INISHIE  = 7; // 古の隠れ里

// ★修正ここまで★-----------------

bool isFirstLoop = true;

void PushRL(int delay_time_ms);
int PushKey(char* keyname, int holdtime, int delaytime);
void TiltLeftStick(int direction_deg, double power,unsigned long int holdtime, unsigned long int delaytime);
void Die(void);

void JumpTo(int destination){
  // destination: cursor where you want to go in map (ArceusPhone).
  int i=0;
  PushKey("-", HOLDTIME, 1200);
  PushKey("X", HOLDTIME, 1000);
  for(i=0; i<destination; i++)PushKey("down", HOLDTIME, 250);
  PushKey("A", HOLDTIME, 3300);
  return;
}
void Turn(int degree){
  TiltLeftStick( degree, 0.3, 140, 300);
  PushKey("ZL", HOLDTIME, 1000);
  return; 
}
void Dash(double second){
  TiltLeftStick( 0, 1.0, second*1000UL, 300);
  return;
}
void Dash(double second, double second_interruptA){
  TiltLeftStick( 0, 1.0, 0, second_interruptA*1000UL); // 傾けて
  PushKey("A", HOLDTIME, (second - second_interruptA)*1000UL );
  TiltLeftStick( 0, 0.0, 0, 300); // 傾きをもどす
  return;
}

void PokeThrow(int delaytime=300, int holdingballtime = 250){
  // ボールを構えて
  SwitchControlLibrary().PressButtonZR(); delay(holdingballtime);
  // ボールを投げる
  SwitchControlLibrary().ReleaseButtonZR(); delay(delaytime);
  return;
}
void RidePoke(void){
  PushKey("+", HOLDTIME, 1200);
  return;
}

void Dig(void){
  PushKey("Y", HOLDTIME, 400);
  return;
}

void DashBack(void){ // call this function after Dig()
  TiltLeftStick( 180, 1.0, 3500, 300);
  PushKey("B", HOLDTIME, 300);
  return;
}

void BackToJubilifeVillage(void){
  // 山頂ベースに飛んで
  JumpTo(SANCHO);

  // 博士に話しかける
  TiltLeftStick( 48, 1.0, 900, 300);
  PushKey("A", HOLDTIME, 900);    // 報告できることは 特にないようですね ▼
  PushKey("A", HOLDTIME, 700);    // これから どうするのですか？ ▼
  PushKey("A", HOLDTIME, 700);    // →調査を続ける
  PushKey("down", HOLDTIME, 350); // →ムラに戻る
  PushKey("A", HOLDTIME, 1200);   // では コトブキムラに戻りましょう 大丈夫です 警備隊も一緒ですよ ▼
  PushKey("A", HOLDTIME, 12000);  // 移動中… 
  return;
}

void GotoCoronetHighlands(void){
  int i=0;
  // 表門前に飛んで
  JumpTo(OMOTEMON);

  // デンスケに話しかける
  TiltLeftStick( 23, 1.0, 2000, 500); // 外に出るのか？気をつけてな or ポケモン大大大発生の 報告があったらしいぞ！ 気をつけてな
  PushKey("A", HOLDTIME, 1200); // マップを開く
  if(isFirstLoop){
    TiltLeftStick( 0, 1.0, 1700, 500); // カーソルを外にはずして
    for(i=0; i<TENGAN; i++)PushKey("down", HOLDTIME, 250); // 「天冠の山麓」にカーソルをあわせる
  }
  PushKey("A", HOLDTIME, 600); // 「天冠の山麓」を選択

  for(i=0; i<SANCHO ; i++)PushKey("down", HOLDTIME, 250); // 「山頂ベース」を選択
  PushKey("A", HOLDTIME, 12000); // 移動中…

  return;  
}

void setup() {
   for(int i=0; i < 5 ; i++)PushKey("B", HOLDTIME, 700);
}

void loop() {

  // 振り返ってガチグマライド掘り起こしポイントへ


  // 超左バージョン
  if(isFirstLoop)JumpTo(SANCHO);
  Turn(169); 
  Dash(15.8, 9.63); // クスリソウを拾う
  RidePoke();
  Dig();
  DashBack();

  // 左バージョン
  JumpTo(SANCHO);
  Turn(177); 
  Dash(16.9);
  RidePoke();
  Dig();
  TiltLeftStick( 180, 1.0, 1600, 300); // ここにもずれることがある
  Dig();
  DashBack();
  
  // 真ん中バージョン
  JumpTo(SANCHO);
  Turn(189); 
  Dash(18.4, 16.64); // ごりごりミネラル を拾う
  RidePoke();
  Dig();
  DashBack();

  // 右バージョン
  JumpTo(SANCHO);
  Turn(202); 
  Dash(15.2);
  RidePoke();
  Dig();
  TiltLeftStick( 180, 1.0, 13000, 2800); // 一番右は、まれにドータクン・ドーミラーに索敵されるので走って基地側へ

  // Die(); // debug


  // コトブキムラに戻る
  BackToJubilifeVillage();

  // 天冠の山麓（山頂ベース）に戻る
  GotoCoronetHighlands();

  isFirstLoop = false;
}

void PushRL(int delay_time_ms){
  SwitchControlLibrary().PressButtonR();
  SwitchControlLibrary().PressButtonL();
  delay(HOLDTIME);
  SwitchControlLibrary().ReleaseButtonR();
  SwitchControlLibrary().ReleaseButtonL();
  delay(delay_time_ms);
  return;
}
int PushKey(char* keyname, int holdtime, int delaytime){
  // ホームボタン・方向キーはRight, Left, Up, Down, Homeなど2文字以上で入力。
  // その他ボタン入力は1文字（A,B,X,Y,R,L,+,-）ZR・ZLにも対応
  // 同時押しは非対応
  
  if(strlen(keyname)==1){
    switch(keyname[0]){
      case 'A': case 'a': // A
        SwitchControlLibrary().PressButtonA(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonA(); delay(delaytime);
      break;
      case 'B': case 'b': // B
        SwitchControlLibrary().PressButtonB(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonB(); delay(delaytime);
      break;
      case 'X': case 'x': // X
        SwitchControlLibrary().PressButtonX(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonX(); delay(delaytime);
      break;
      case 'Y': case 'y': // Y
        SwitchControlLibrary().PressButtonY(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonY(); delay(delaytime);
      break;
      case 'L': case 'l': // L
        SwitchControlLibrary().PressButtonL(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonL(); delay(delaytime);
      break;
      case 'R': case 'r': // R
        SwitchControlLibrary().PressButtonR(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonR(); delay(delaytime);
      break;
      case 'H': case 'h': // Home
        SwitchControlLibrary().PressButtonHome(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonHome(); delay(delaytime);
      break;
      case '+': case 'p': case 'P': // Plus
        SwitchControlLibrary().PressButtonPlus(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonPlus(); delay(delaytime);
      break;
      case '-': case 'm': case 'M': // Minus
        SwitchControlLibrary().PressButtonMinus(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonMinus(); delay(delaytime);
      break;
      default:
      break;
    }
  }else if(strlen(keyname)>=2){
    switch(keyname[0]){
      case 'z': case 'Z': // ZR/ZL
        if(keyname[1]=='R'||keyname[1]=='r'){
          SwitchControlLibrary().PressButtonZR(); delay(holdtime);
          if(holdtime>0)SwitchControlLibrary().ReleaseButtonZR(); delay(delaytime);
        }
        if(keyname[1]=='L'||keyname[1]=='l'){
          SwitchControlLibrary().PressButtonZL(); delay(holdtime);
          if(holdtime>0)SwitchControlLibrary().ReleaseButtonZL(); delay(delaytime);
        }
      break;
      case 'r': case 'R': // right
        SwitchControlLibrary().MoveHat(2); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().MoveHat(8); delay(delaytime);
      break;
      case 'l': case 'L': // left
        SwitchControlLibrary().MoveHat(6); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().MoveHat(8); delay(delaytime);
      break;
      case 'u': case 'U': // up
        SwitchControlLibrary().MoveHat(0); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().MoveHat(8); delay(delaytime);
      break;
      case 'd': case 'D': // down
        SwitchControlLibrary().MoveHat(4); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().MoveHat(8); delay(delaytime);
      break;
      case 'H': case 'h': // Home
        SwitchControlLibrary().PressButtonHome(); delay(holdtime);
        if(holdtime>0)SwitchControlLibrary().ReleaseButtonHome(); delay(delaytime);
      default:
      break;  
    }
  }else{
    return -1;
  }
  return strlen(keyname);
}
void TiltLeftStick(int direction_deg, double power,unsigned long int holdtime, unsigned long int delaytime){
  double rad = (double)direction_deg*PI/180.0; // 弧度法(ラジアン)変換
  int x, y;
  x = (double)128*sin(rad)*power;
  y = (double)-128*cos(rad)*power;
  x += 128; y += 128;
  if(x >= 255) x=255; if(x <= 0) x=0;
  if(y >= 255) y=255; if(y <= 0) y=0;

  SwitchControlLibrary().MoveLeftStick(x,y);
  if(holdtime> 0){ // holdtime=0のときは押しっぱなし。
    delay(holdtime);
    SwitchControlLibrary().MoveLeftStick(128,128); // 傾きを直す
  }
  if(delaytime>0) delay(delaytime);
  return;
}

void Die(void){
  for(;;)delay(100);
}
