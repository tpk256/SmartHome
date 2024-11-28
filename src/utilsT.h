struct OnlyAccessUsers{
    bool HasAdmin();
    bool ResetAdmin();
    bool DeleteUsers();
    bool AddUser(const char* cmd);
    bool AddAdmin(int userId);
    bool ExistUser(int);
    bool IsAdmin(int);

};
