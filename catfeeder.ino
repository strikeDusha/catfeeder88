
#include "FastBot.h"
#define motor 14
#define zp 12
#define zm 13

char ssid[] = "iPhone (Андрей)";         
char password[] = "12345678";     

FastBot bot("6389648544:AAE91bpQdAxPBYas3tTSS2xI4sD5mq-ZtR4");

int timefeeding = 5000;
int interval = 8;

unsigned long Bot_lasttime;
bool imode = false;
bool beep = true;
bool notif = true;
void feed() {

    digitalWrite(motor, 1);
    beep ? digitalWrite(zp,1):digitalWrite(zp,0);
    digitalWrite(zm,0);
    delay(timefeeding);
    digitalWrite(motor, 0);
    digitalWrite(zp,0);
    digitalWrite(zm,0);
}
void handleFeedCommand(String chat_id) {
    feed();
    Serial.println("1"); 
    if(notif){
      bot.sendMessage("Корм успешно насыпан✅\nНажмите /start для основного меню",chat_id);
      bot.sendMessage("Новое кормление\n"+ chat_id+"\nОт пользователя","865660031"); 
    }
}
void handleNewMessages(FB_msg& msg) {
    String data = msg.data;
    String chat_id = msg.chatID;
    String text =msg.text;
    if(text=="/start"){
    String welcome = "Приветствую тебя.\n";
  	welcome += "Это котокормилка, управляемая через Telegram.\n\n";
    welcome += "Для ручного кормления нажмите `Покормить`\n";
    welcome += "Для включения/выключения писка при кормлении нажмите `Вкл/выкл зуммер`\n";
 		welcome += "Интервал кормления "+String(interval)+" ч\n\n";
  	welcome += "Время насыпания "+String(timefeeding/1000)+" сек\n\n";
    if(imode){
    welcome += "Режим автоматического кормления включен✅.\n\n";
    welcome += "Для изменения нажмите на кнопку `Режим кормления`\n\n";
    }else{
    welcome += "Режим автоматического кормления выключен☑️.\n\n";
    welcome += "Для изменения нажмите на кнопку `Режим кормления`\n\n";
    }
    notif?welcome+="Уведомления включены✅\n":welcome+="Уведомления включены✅\n";
    beep?welcome+="Зуммер включен✅\n":welcome+="Зуммер отключен☑️\n";
  	welcome += "Выберите действие:";
  	bot.showMenuText(welcome,"Покормить \n Вкл/выкл зуммер \t Режим кормления \t Вкл/выкл увед" , chat_id);
    }

    
    if (text=="Режим кормления"){
      if(imode){ bot.sendMessage("Кормление по расписанию выключено\nНажмите /start для основного меню",chat_id);
        imode = false;
       
        
      }else{bot.sendMessage("Кормление по расписанию включено\nНажмите /start для основного меню",chat_id);
        imode = true;
        
        
      }
    }
    if(text == "Вкл/выкл увед"){
       if(notif){bot.sendMessage("Уведомления отключены\nНажмите /start для основного меню",chat_id);
        notif = false;
        
        
      }else{bot.sendMessage("Уведомления включены\nНажмите /start для основного меню",chat_id);
        notif = true;
        
        
      }
    }
    if(text == "Покормить"){
      handleFeedCommand(chat_id);}
    if (text=="Вкл/выкл зуммер"){
      if(beep){bot.sendMessage("Звуковое сообщение отключено\nНажмите /start для основного меню",chat_id);
        beep = false;
        
        
      }else{bot.sendMessage("Звуковое сообщение включено\nНажмите /start для основного меню",chat_id);
        beep = true;
        
        
      }
    }
	 }
  

      


void setup() {

  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  bot.setTextMode(FB_MARKDOWN);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(motor,OUTPUT);
  pinMode(zp,OUTPUT);
  pinMode(zm, OUTPUT);
  bot.showMenu("");

  delay(10);
  bot.attach(handleNewMessages);
}

void loop() {
    bot.tick();
}

