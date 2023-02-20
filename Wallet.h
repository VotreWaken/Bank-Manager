/*
The wallet class aggregates the already existing Card class
by storing it in a vector
*/
#ifndef WALLET_H
#define WALLET_H
#include <vector>
#include "Card.h"
// Class Wallet 
class Wallet
{
protected:
    // Wallet Fields
    std::vector<Card*> cards;
public:

    // Add Card To Wallet
    virtual void addCard(Card* card)
    {
        cards.push_back(card);
    }

    // Print all Cards In Wallet
    virtual void printCards()
    {
        for (Card* card : cards)
        {
            card->print();
            cout << endl;
        }
    }
};

// Derived class for online wallets
class OnlineWallet : public Wallet
{
public:
    // Add Card To Wallet
    void addCard(Card* card)
    {
        if (dynamic_cast<DebitCard*>(card))
        {
            cards.push_back(card);
        }
        else {
            cout << "Only debit cards can be added to an online wallet." << endl;
        }
    }

    // Print all Cards In Wallet
    virtual void printCards()
    {
        cout << "Online Wallet Cards" << endl;
        Wallet::printCards();
    }
};

// Derived class for physical wallets
class PhysicalWallet : public Wallet
{
public:
    // Add Card To Wallet
    void addCard(Card* card)
    {
        if (dynamic_cast<CreditCard*>(card))
        {
            cards.push_back(card);
        }
        else
        {
            cout << "Only credit cards can be added to a physical wallet." << endl;
        }
    }

    // Print all Cards In Wallet
    virtual void printCards()
    {
        cout << "Physical Wallet Cards" << endl;
        Wallet::printCards();
    }
};
#endif
