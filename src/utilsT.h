struct OnlyAccessUsers{
    bool HasAdmin();
    bool ResetAdmin();
    bool DeleteUsers();
    bool AddUser(const char* userId, short len);
    bool AddAdmin(const char* userId, short len);
    bool ExistUser(const char*);

};
