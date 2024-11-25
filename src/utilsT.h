struct OnlyAccessUsers{
    bool HasAdmin();
    bool ResetAdmin();
    bool DeleteUsers();
    bool AddUser(const char* cmd);
    bool AddAdmin(const char* userId);
    bool ExistUser(const char*);
    bool IsAdmin(const char*);

};
