#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H 1
#include<bits/stdc++.h>
#include "scope_table.h"
using namespace std;


class SymbolTable {
    ScopeTable* currentScope;
    int totalBuckets;
public:
    SymbolTable(int totalBuckets) {
        this->totalBuckets = totalBuckets;
        this->currentScope = nullptr;
        enterScope();
    }

    string getCurrentScopeId() {
        return this->currentScope->getId();
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

    bool insert(SymbolInfo* newSymbol) {
        if(this->currentScope == nullptr) {
            this->currentScope = new ScopeTable(totalBuckets);
            this->currentScope->setParentScope(nullptr);
            this->currentScope->setId();
        }
        return currentScope->insert(newSymbol);
    }
    

    bool remove(string name) {
        return currentScope->remove(name);
    }

    SymbolInfo* lookupAll(string name) {
        ScopeTable* scope = this->currentScope; //scope is used as iterator
        SymbolInfo* symbol;
        while(scope != nullptr) {
            symbol = scope->lookup(name);
            if(symbol != nullptr) {
                return symbol;
            }
            scope = scope->getParentScope();
        }
        cout<<name<<" Not found\n";
        return nullptr;
    }

    SymbolInfo* lookupCurrent(string name) {
        ScopeTable* scope = this->currentScope; 
        SymbolInfo* symbol;
        symbol = scope->lookup(name);
        if(symbol != nullptr) {
            return symbol;
        }
        cout<<name<<" Not found\n";
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

#endif