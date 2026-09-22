#ifndef CellJudgmentH
#define CellJudgmentH

#include "SiteConfig.h"

// 공통 규격 판정. 항목별 불량은 화면 표시용, result는 최종 대표 판정이다.
// 수신 여부는 기존 irValueReceived/ocvValueReceived로 별도 관리한다.
struct TCellJudgment
{
    bool contactNg;
    bool irNg;
    bool ocvNg;
    int result;
};

// 화면/PLC에 접근하지 않는다. 경계값 포함 OK, 대표 판정은 접촉 > IR > OCV.
inline TCellJudgment JudgeCellValues(double ir, double ocv,
    double irMin, double irMax, double ocvMin, double ocvMax)
{
    TCellJudgment judgment;
    judgment.contactNg = ir == 999;
    judgment.irNg = ir < irMin || ir > irMax;
    judgment.ocvNg = ocv < ocvMin || ocv > ocvMax;
    judgment.result = judgment.contactNg ? CELL_CONTACT_NG :
        (judgment.irNg ? CELL_IR_NG : (judgment.ocvNg ? CELL_OCV_NG : CELL_OK));
    return judgment;
}
#endif
