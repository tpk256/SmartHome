struct OnlyAccessUsers{
    bool HasAdmin();
    bool ResetAdmin();
    bool DeleteUsers();
    bool AddUser(const char* userId);
    bool AddAdmin(const char* userId);
    bool ExistUser(const char*);
    bool IsAdmin(const char*);

};
