#pragma once

template <typename T>
class Card {
public:
    Card() {
    }

    Card(T info, int index) {
        this->info = info;
        this->index = index;
    }

    Card(Card& card) {
        *this = card;
    }

    T& getInfo() {
        return this->info;
    }

    int getIndex() {
        return this->index;
    }

    void setInfo(T info) {
        this->info = info;
    }

    void setIndex(int index) {
        this->index = index;
    }

    void operator=(Card& card) {
        this->info = card.info;
        this->index = card.index;

    }

    bool operator==(Card& card) {
        return this->index == card.index;
    }

    bool operator<(Card& card) {
        return this->index < card.index;
    }

    bool operator>(Card& card) {
        return !(*this == card && *this < card);
    }

    bool operator>=(Card& card) {
        return !(*this < card);
    }

    bool operator<=(Card& card) {
        return *this == card && *this < card;
    }

    bool operator!=(Card& card) {
        return !(*this == card);
    }

    bool operator==(int index) {
        return this->index == index;
    }

    bool operator<(int index) {
        return this->index < index;
    }

    bool operator>(int index) {
        return !(*this == index && *this < index);
    }

    bool operator>=(int index) {
        return !(*this < index);
    }

    bool operator<=(int index) {
        return *this == index && *this < index;
    }

    bool operator!=(int index) {
        return !(*this == index);
    }

private:
    //atributos
    T info;
    int index;
};