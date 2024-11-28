#include <FastBot2.h>
#include <cstring>
#include <string.h>
#include <cctype>
#define MAX_USERS 4
#define ADMIN_INDEX 0
#define LEN_USER_ID 11
#define D2 4
#define D1 5
#define LEN_COMMAND_ADD_USER 9


struct OnlyAccessUsers{
    Text _users[5];
    int _countUsers = 0;
    bool _hasAdmin = false;

    OnlyAccessUsers() {
        for (int i = 0; i <= MAX_USERS; ++i) {
            _users[i] = "";
        }
    }
    bool HasAdmin() { 
        return _users[0].length() != 0;
    }

    bool ExistUser(Text userId){
        if (!_countUsers) return false;

        for( int i = 1; i <= _countUsers; i++){
            if (_users[i]==userId) return true;
        }
        return false;
    }
    bool ResetAdmin(){
        if (HasAdmin()){
            _users[0] = "";
            _hasAdmin = false;
            return true;
        }
        return false;
    }
    bool DeleteUsers(){
        // Удаляет всех пользователей, кроме админа.
        if (_countUsers == 0) return false;
        short i = _countUsers;
        for( ; i >= 1; i--){
            _users[i] = "";
        }
        _countUsers = i;
        return true;

    }
    bool _IsValidUserId(const char* userId){
        // Полагаем, что длина UserId in [6, 11]
        short len = strlen(userId);
        if (len <= 5 || len > 11) return false; // maybe will be bug
        for (short i = 0; i < len; i++)
            if (!isdigit( userId[i])) return false;
        return true;
    }
    /*
    Text _ParseUserId(Text cmd){
        Text ans;;
        if (!ans) return ans;
        for(short i = 9; i < strlen(cmd); i++){
            ans[i - 9] = cmd[i]; 
        }
        return ans;

    }*/
    /*
    bool AddUser(Text cmd){
        if (_countUsers == MAX_USERS)
            return false;
        char *userId = _ParseUserId(cmd);
        if (!userId) return false; // значит, что памяти нет под юзера(нулевой указатель)
        if(!_IsValidUserId(userId)) return false;
        _users[++_countUsers] = userId;
        return true;
    }*/
    bool AddAdmin(Text userId){
        if (HasAdmin()) return false;
        _hasAdmin = true;
        _users[ADMIN_INDEX] =  userId;
        return true;
    }

    bool IsAdmin(Text userId){
        if (!HasAdmin()) return false;
        Serial.print("State admin: ");
        Serial.println(_users[ADMIN_INDEX]);
        Serial.println(userId);
        Serial.println(userId == _users[ADMIN_INDEX]);
        return  userId.compare(_users[ADMIN_INDEX]);
    }

};







OnlyAccessUsers data_bot;
FastBot2 bot;

const char* SSID = "tps";
const char* PASSWORD = "2743113077"; 


// Работу со структурой сделать через команды.

bool isCommand(Text text){
    Serial.print("ss:\t");
    Serial.println(text[0]);
    Serial.println(text);
    return text[0] == '/';
}


void ExecuteCommand(fb::Update& u){
    fb::Message msg;
    fb::Menu menu;
    msg.chatID = u.message().chat().id();
    
    Text command = u.message().text(), userId = u.message().from().id();
  
    if (!isCommand(command)){
      msg.text = "Please use command";
      bot.sendMessage(msg);
      return;
    }
    if (command == "/start" ){
      Serial.print("admin_state: ");
      Serial.println(data_bot.HasAdmin());
      if(data_bot.HasAdmin()){
          if (!data_bot.ExistUser(userId)) {
              msg.text = "ACCESS DENIED!";
              bot.sendMessage(msg);
              return;
          } 
      }
      else{
        data_bot.AddAdmin(userId);
        }

        msg.text = "Hello, admin";
        menu.addButton("/help").addButton("/door");
        msg.setMenu(menu);
        Serial.print("userId: ");
        Serial.println(data_bot._users[0]);
    }
    else if((command == "/door") && (data_bot.ExistUser(userId) || data_bot.IsAdmin(userId)) ){
      fb::InlineMenu menu;
      msg.text = "Open the door?\0";
      menu.addButton("Yes", "open_door_yes");
      menu.addButton("No", "open_door_no");
      msg.setInlineMenu(menu);
    }
    else if (( command == "/help") && (data_bot.ExistUser(userId) || data_bot.IsAdmin(userId))){
      // Вывод справочной информации

    }
    /*else if(
      !strncmp("/add_user", command, LEN_COMMAND_ADD_USER) && 
      data_bot.IsAdmin(userId)){
        if (data_bot.AddUser(command))
          msg.text = "Success added";
        else
          msg.text = "Error add";

    }
    */
    else if((command == "/delete_users"  ) && 
      data_bot.IsAdmin(userId)){
      // Дописать реализацию
    }
    else if((command == "/reset_admin" ) && 
      data_bot.IsAdmin(userId)){
      // Дописать реализацию
    }
    else{
      msg.text = "Unknown command!\0";

    }
    bot.sendMessage(msg);
}


void OpenDoor(fb::Update& u){
    fb::Message msg;
  if (!strcmp(u.query().data().c_str(), "open_door_yes")){
     
  
    msg.chatID = u.query().message().chat().id();
    msg.text = "Opened door";
    bot.sendMessage(msg);
    digitalWrite(D2, HIGH); 
    delay(5000); // 100ms 
  
  }
  digitalWrite(D2, LOW); 
}


void update (fb::Update& u){
    // Добавляем конкретный список userov tg (id)


    // Нужно inline конпку сделать,
    // когда прилетает да, то мы посылаем сигнал по пину и после отправляет измененное сообщение
    // что открыли или просто новое отправляем
    

    // ЛОГИКА ПОСЫЛАЕТСЯ КОМАНДА МЕНЮ, А МЫ ИНЛАЙН КНОПКУ ОТКРЫИТЬ
  
    if (u.isQuery()){
        OpenDoor(u);
     }
    else if (u.isMessage()){
        ExecuteCommand(u);
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
  bot.skipUpdates(-1);
  bot.setLimit(3);
  bot.setPollMode(fb::Poll::Sync, 4000);
  bot.attachUpdate(update);
}

void loop() {
  bot.tick();
}
