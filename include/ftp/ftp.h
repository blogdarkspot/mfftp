namespace FTP {

enum class Command {
    USER,
    QUIT,
    PORT,
    TYPE,
    MODE,
    STRU,
    RETR,
    STOR,
    NOOP
};

enum class Reply {
    CODE_110,
    CODE_120,
    CODE_125,
    CODE_150,
    CODE_200,
    CODE_202,
    CODE_211,
    CODE_212,
    CODE_213,
    CODE_214,
    CODE_215,
    CODE_220,
    CODE_221,
    CODE_225,
    CODE_226,
    CODE_227,
    CODE_230,
    CODE_250,
    CODE_257,
    CODE_331,
    CODE_332,
    CODE_350,
    CODE_421,
    CODE_425,
    CODE_426,
    CODE_450,
    CODE_451,
    CODE_452,
    CODE_500,
    CODE_501,
    CODE_502,
    CODE_503,
    CODE_504,
    CODE_530,
    CODE_532,
    CODE_550,
    CODE_551,
    CODE_552,
    CODE_553
};

};