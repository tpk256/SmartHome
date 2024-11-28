#include <FastBot2.h>
#include <cstring>
#include "utilsT.h"


#define DATA_OPEN_DOOR "open_door_yes"
#define D2 4
#define D1 5
#define LEN_COMMAND_ADD_USER 9



OnlyAccessUsers data_bot;
FastBot2 bot;

const char* SSID = "tps";
const char* PASSWORD = "2743113077"; 


// Работу со структурой сделать через команды.

bool isCommand(Text text){
    return text[0] == '/';
}

void executeCommand(fb::Update& u){
    fb::Message msg;
    fb::Menu menu;
    fb::InlineMenu inlineMenu;
    msg.chatID = u.message().chat().id();
    Text command = u.message().text(); 
    const char* userId = u.message().from().id().c_str();


    if (!isCommand(command)){
      msg.text = "Please use command";
      bot.sendMessage(msg);
      return;
    }
    if (command == "/start"){
      if(data_bot.HasAdmin())
          if (!data_bot.ExistUser(userId)) {
              msg.text = "ACCESS DENIED!";
              bot.sendMessage(msg);
              return;
          }
            
      else
        data_bot.AddAdmin(userId);
        
        menu.addButton("/help").addButton("/door");
        msg.text = "Hello admin!";
        msg.setMenu(menu);
    }
    else if((command == "/door" ) && (data_bot.ExistUser(userId) || data_bot.IsAdmin(userId))){
        
        msg.text = "Open the door?\0";
        inlineMenu.addButton("Yes", DATA_OPEN_DOOR);
        inlineMenu.addButton("No", "open_door_no");
        msg.setInlineMenu(inlineMenu);
    }
    else if ((command == "/help" ) && (data_bot.ExistUser(userId) || data_bot.IsAdmin(userId))){
      // Вывод справочной информации

    }
    // else if(
    //   !strncmp("/add_user", command, LEN_COMMAND_ADD_USER) && 
    //   data_bot.IsAdmin(userId)){
    //     if (data_bot.AddUser(command))
    //       msg.text = "Success added";
    //     else
    //       msg.text = "Error add";
    //}
    else if( (command == "/delete_users") && 
      data_bot.IsAdmin(userId)){
      // Дописать реализацию
    }
    else if((command == "/reset_admin") && 
      data_bot.IsAdmin(userId)){
      // Дописать реализацию
    }
    else{
      msg.text = "Unknown command!\0";

    }
    bot.sendMessage(msg);
}


void openDoor(fb::Update& u){
  Serial.println("Door opened!");
}


void update (fb::Update& u){
    // Добавляем конкретный список userov tg (id)


    // Нужно inline конпку сделать,
    // когда прилетает да, то мы посылаем сигнал по пину и после отправляет измененное сообщение
    // что открыли или просто новое отправляем
    

    // ЛОГИКА ПОСЫЛАЕТСЯ КОМАНДА МЕНЮ, А МЫ ИНЛАЙН КНОПКУ ОТКРЫИТЬ
  
    if (u.isQuery() && u.query().data() == DATA_OPEN_DOOR){
        openDoor(u);
     }
    else if (u.isMessage()){
        executeCommand(u);
    }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(SSID,  PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected");

  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW); 
  bot.setToken("7282964831:AAFpXPLc0eODNVYyO5QNGbrzgDYIfKC3wGE");
  bot.skipUpdates(0);
  bot.setLimit(3);
  bot.setPollMode(fb::Poll::Sync, 4000);
  bot.attachUpdate(update);
}

void loop() {
  bot.tick();
}
