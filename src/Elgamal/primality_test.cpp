class IPrimalityTest {
public:
    virtual bool check_primary(int value, double minProb) = 0;
};

class PrimalityTest: IPrimalityTest {
private:
    bool checkMinProbRange(double minProb) {
        return (minProb >= 0.5 && minProb < 1);
    }

    bool checkEvenNumber(int value) {
        return (value > 2 && (value % 2)==0); //TODO подумать об эффективной проверке на четность(последний бит)
    }
public:
    bool checkProbRangeAndEvenNumber(int value, double minProb) {
        if (!::PrimalityTest::checkMinProbRange(minProb))
            return false; //TODO придумать действия при ошибках как в контрактах
        if (::PrimalityTest::checkEvenNumber(value))
            return false;
        return true;
    }
};

class FermatTest: public PrimalityTest {
    bool check_primary(int value, double minProb) override {
        if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
            return false;


    }
};

class SolovayStrassenTest: public PrimalityTest {
    bool check_primary(int value, double minProb) override {
        if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
            return false;
    }
};

class MillerRabinTest: public PrimalityTest {
    bool check_primary(int value, double minProb) override {
        if (!::PrimalityTest::checkProbRangeAndEvenNumber(value, minProb))
            return false;
    }
};