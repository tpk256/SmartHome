struct OnlyAccessUsers{
    bool HasAdmin();
    bool ResetAdmin();
    bool DeleteUsers();
    bool AddUser(const char* );
    bool AddAdmin(const char* );
    bool _IsValidUserId(const char* );
    char * _ParseUserId(const char* );
    bool ExistUser(const char*);
    bool IsAdmin(const char*);

};
