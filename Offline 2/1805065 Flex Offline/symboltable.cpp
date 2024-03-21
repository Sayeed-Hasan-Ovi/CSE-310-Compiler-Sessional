#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class SymbolInfo{
    string symbolName;
    string symbolType;
    SymbolInfo* next;
public:
    SymbolInfo(string symbolName, string symbolType) {
        this->symbolName = symbolName;
        this->symbolType = symbolType;
        this->next = nullptr;
    }

    string getSymbolName() {
        return symbolName;
    }

    string getSymbolType() {
        return symbolType;
    }

    SymbolInfo* getNext() {
        return next;
    }

    void setNext(SymbolInfo* next) {
        SymbolInfo* temp = this->next;
        this->next = next;
        if(next != nullptr)
            delete temp;
    }

    void print() {
        cout<<symbolName<<" : "<<symbolType;
    }

    ~SymbolInfo() {
       
    }
};

class ScopeTable {
    SymbolInfo** buckets;
    ScopeTable* parentScope;
    int totalBuckets;
    int childrenCount;
    string id;
public:
    ScopeTable(int totalBuckets) {
        this->totalBuckets = totalBuckets;
        this->buckets = new SymbolInfo*[totalBuckets];
        this->childrenCount = 0;
        for(int i = 0; i < totalBuckets; i++) {
            buckets[i] = nullptr;
        }
    }

    uint32_t sdbmhash(string str) {
        uint32_t hash = 0;
        int i = 0, n = str.length();
        while (i < n) {
            hash = str[i] + (hash << 6) + (hash << 16) - hash;
            i++;
        }
        return hash%totalBuckets;
    }

    ScopeTable* getParentScope() {
        return this->parentScope;
    }

    void setParentScope(ScopeTable* newParentScope) {
        this->parentScope = newParentScope;
    }

    string getId() {
        return id;
    }

    void setId() {
        if(this->parentScope == nullptr) {
            this->id = "1";
            return;
        }
        this->id = this->parentScope->getId()+"."+to_string(this->parentScope->getChildrenCount());
        //cout<<"New ScopeTable with id "<<this->id<<" created\n";
    }

    int getChildrenCount() {
        return childrenCount;
    }

    void incChildrenCount() {
        this->childrenCount++;
    }

    bool insert(string name, string type) {
        int bucketNo = sdbmhash(name);
        int i = 0;
        SymbolInfo* symbol = buckets[bucketNo];
        SymbolInfo* prev = nullptr;
        while(symbol != nullptr) {
            if(symbol->getSymbolName() == name) {
                cout<<"<";
                symbol->print();
                cout<<">";
                cout<<" already exists in current ScopeTable\n";
                return false;
            }
            prev = symbol;
            symbol = symbol->getNext();
            i++;
        }
        SymbolInfo* newSymbol = new SymbolInfo(name, type);
        if(prev == nullptr) {              //Case: the bucket is empty
            buckets[bucketNo] = newSymbol;
        } else {                    //Case: the bucket has at least one element
            prev->setNext(newSymbol);
        }
        cout<<"Inserted in ScopeTable# "<<this->id<<" at position "<<bucketNo<<", "<<i<<"\n";
        return true;
    }

    bool insert(string name, string type, ofstream& logout) {
        int bucketNo = sdbmhash(name);
        int i = 0;
        SymbolInfo* symbol = buckets[bucketNo];
        SymbolInfo* prev = nullptr;
        while(symbol != nullptr) {
            if(symbol->getSymbolName() == name) {
                logout<<"<"<<symbol->getSymbolName()<<", "<<symbol->getSymbolType()<<">";
                logout<<" already exists in current ScopeTable\n";
                logout<<"\n";
                return false;
            }
            prev = symbol;
            symbol = symbol->getNext();
            i++;
        }
        SymbolInfo* newSymbol = new SymbolInfo(name, type);
        if(prev == nullptr) {              //Case: the bucket is empty
            buckets[bucketNo] = newSymbol;
        } else {                    //Case: the bucket has at least one element
            prev->setNext(newSymbol);
        }

        return true;
    }

    bool remove(string name) {
        int bucketNo = sdbmhash(name);
        SymbolInfo* symbol = buckets[bucketNo];
        SymbolInfo* prev = nullptr;
        int i = 0;

        while(symbol != nullptr) {
            if(symbol->getSymbolName() == name) {
                if(prev == nullptr) {
                    buckets[bucketNo] = symbol->getNext(); //1st element in bucket is being deleted
                } else {
                    prev->setNext(symbol->getNext());
                }
                cout<<"Deleted Entry "<<bucketNo<<", "<<i<<" from current ScopeTable\n";
                delete symbol;
                return true;
            }
            prev = symbol;
            symbol = symbol->getNext();
            i++;
        }
        cout<<name<<" not found\n";
        return false;
    }

    SymbolInfo* lookup(string name) {
        int bucketNo = sdbmhash(name);
        SymbolInfo* symbol = buckets[bucketNo];
        int i = 0;
        while(symbol != nullptr) {
            if(symbol->getSymbolName() == name) {
                cout<<"Found in ScopeTable# "<<id<<" at position "<<bucketNo<<", "<<i<<"\n";
                return symbol;
            }
            symbol = symbol->getNext();
        }
        return nullptr;
    }

    void print() {
        cout<<"ScopeTable # "<<this->id<<"\n";
        for(int i = 0; i < totalBuckets; i++) {
            SymbolInfo* symbol = buckets[i];
            if(buckets[i] == nullptr)
                continue;
            cout<<i<<" --> ";
            while(symbol != nullptr) {
                cout<<" < ";
                symbol->print();
                cout<<"> ";
                symbol = symbol->getNext();
            }
            cout<<"\n";
        }
    }

    void print(ofstream& logout) {
        logout<<"ScopeTable # "<<this->id<<"\n";
        for(int i = 0; i < totalBuckets; i++) {
            if(buckets[i] == nullptr)
                continue;
            SymbolInfo* symbol = buckets[i];
            logout<<i<<" --> ";
            while(symbol != nullptr) {
                logout<<"<"<<symbol->getSymbolName()<<", "<<symbol->getSymbolType()<<"> ";
                symbol = symbol->getNext();
            }
            logout<<"\n";
        }
    }
    ~ScopeTable() {
        //cout<<"ScopeTable with id "<<id<<" is removed\n";
        // if(this->id == "1") {
        //     cout<<"Destroying the First Scope\n";
        // }
        for(int i = 0; i < totalBuckets; i++) {
            while(buckets[i] != nullptr) {
                SymbolInfo* temp = buckets[i]->getNext();
                delete buckets[i];
                buckets[i] = temp; 
            }
        }
        delete[] buckets;
    }
};

class SymbolTable {
    ScopeTable* currentScope;
    int totalBuckets;
public:
    SymbolTable(int totalBuckets) {
        this->totalBuckets = totalBuckets;
        this->currentScope = nullptr;
        enterScope();
    }

    void enterScope() {
        ScopeTable* newScope= new ScopeTable(totalBuckets);
        if(this->currentScope != nullptr){
            this->currentScope->incChildrenCount();
        }
        newScope->setParentScope(this->currentScope);//making the currentScope as parentScope of newScope
        newScope->setId();  //we first set parentScope then call setId so that we can get parentScope's id to set newScope's id
        this->currentScope = newScope; //making newScope as current scope
    }

    void exitScope() {
        ScopeTable* temp = this->currentScope;
        this->currentScope = temp->getParentScope();
        delete temp;
    }

    bool insert(string name, string type) {
        if(this->currentScope == nullptr) {
            this->currentScope = new ScopeTable(totalBuckets);
            this->currentScope->setParentScope(nullptr);
            this->currentScope->setId();
        }
        return currentScope->insert(name, type);
    }

    bool insert(string name, string type, ofstream& logout) {
        if(this->currentScope == nullptr) {
            this->currentScope = new ScopeTable(totalBuckets);
            this->currentScope->setParentScope(nullptr);
            this->currentScope->setId();
        }
        return currentScope->insert(name, type, logout);
    }

    bool remove(string name) {
        return currentScope->remove(name);
    }

    SymbolInfo* lookup(string name) {
        ScopeTable* scope = this->currentScope; //scope is used as iterator
        SymbolInfo* symbol;
        while(scope != nullptr) {
            symbol = scope->lookup(name);
            if(symbol != nullptr) {
                return symbol;
            }
            scope = scope->getParentScope();
        }
        cout<<"Not found\n";
        return nullptr;
    }

    void printCurrentScopeTable() {
        currentScope->print();
    }

    void printAllScopeTable() {
        ScopeTable* scope = this->currentScope; //scope is used as iterator
        while(scope != nullptr) {
            scope->print();
            cout<<"\n";
            scope = scope->getParentScope();
        }
    }

    
    void printAllScopeTable(ofstream& logout) {
        ScopeTable* scope = this->currentScope; //scope is used as iterator
        while(scope != nullptr) {
            scope->print(logout);
            logout<<"\n";
            scope = scope->getParentScope();
        }
    }

    ~SymbolTable() {
        ScopeTable* scope = this->currentScope;
        while(scope != nullptr) {
            ScopeTable* temp = scope;
            scope = temp->getParentScope();
            delete temp;
        }
    }
};

