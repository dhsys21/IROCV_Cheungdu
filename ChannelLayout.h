#ifndef ChannelLayoutH
#define ChannelLayoutH

#include "SiteConfig.h"

// VCL에 의존하지 않는 공통 화면 좌표 계산. 두 프로그램에서 동일하게 유지한다.
// index는 항상 원래 채널 번호-1이며, 위치와 행/열 표시에만 이 함수를 사용한다.
namespace ChannelLayout
{
struct Position { int row; int column; };
struct Rect { int left; int top; int width; int height; };

inline bool StartsRight(TChannelStartCorner corner)
{
    return corner == CHANNEL_BOTTOM_RIGHT || corner == CHANNEL_TOP_RIGHT;
}
inline bool StartsBottom(TChannelStartCorner corner)
{
    return corner == CHANNEL_BOTTOM_RIGHT || corner == CHANNEL_BOTTOM_LEFT;
}

// 행/열 번호는 시작 모서리를 기준으로 1부터 증가한다. 화면 좌표는 좌상단 기준 0부터.
inline int RowNumber(int index, int rows = CELL_ROW_COUNT, int columns = CELL_COLUMN_COUNT,
    TChannelFillDirection direction = CHANNEL_FILL_DIRECTION)
{
    return (direction == CHANNEL_HORIZONTAL ? index / columns : index % rows) + 1;
}
inline int ColumnNumber(int index, int rows = CELL_ROW_COUNT, int columns = CELL_COLUMN_COUNT,
    TChannelFillDirection direction = CHANNEL_FILL_DIRECTION)
{
    return (direction == CHANNEL_HORIZONTAL ? index % columns : index / rows) + 1;
}
inline Position ForIndex(int index, int rows = CELL_ROW_COUNT, int columns = CELL_COLUMN_COUNT,
    TChannelStartCorner corner = CHANNEL_START_CORNER,
    TChannelFillDirection direction = CHANNEL_FILL_DIRECTION)
{
    Position p;
    p.row = RowNumber(index, rows, columns, direction) - 1;
    p.column = ColumnNumber(index, rows, columns, direction) - 1;
    if(StartsBottom(corner)) p.row = rows - 1 - p.row;
    if(StartsRight(corner)) p.column = columns - 1 - p.column;
    return p;
}

// 화면 크기를 실제 행/열 수로 분할한다. 정수 나눗셈 잔여 픽셀도 분배해 끝 셀이 잘리지 않는다.
// axes=true는 채널 1번 모서리 쪽에 행열 제목 공간을 예약한다.
// 오른쪽 시작이면 세로 제목은 오른쪽, 아래 시작이면 가로 제목은 아래쪽이다.
// 셀 사이 간격 1px, 외곽 2px. axes=false인 메인/교정 화면은 기존 크기를 유지한다.
inline Rect GridCell(int row, int column, int width, int height, bool axes,
    int rows = CELL_ROW_COUNT, int columns = CELL_COLUMN_COUNT,
    TChannelStartCorner corner = CHANNEL_START_CORNER)
{
    const int axisWidth = axes ? 1 + (width - 4) / (columns + 1) : 0;
    const int axisHeight = axes ? 1 + (height - 4) / (rows + 1) : 0;
    const int x0 = 2 + (StartsRight(corner) ? 0 : axisWidth);
    const int y0 = 2 + (StartsBottom(corner) ? 0 : axisHeight);
    const int usableWidth = width - 4 - axisWidth;
    const int usableHeight = height - 4 - axisHeight;
    Rect r;
    r.left = x0 + column * usableWidth / columns;
    r.top = y0 + row * usableHeight / rows;
    r.width = x0 + (column + 1) * usableWidth / columns - r.left - 1;
    r.height = y0 + (row + 1) * usableHeight / rows - r.top - 1;
    return r;
}
// 두 안내 축이 만나는 범례 공간. 채널 1번과 같은 모서리에 놓는다.
inline Rect AxisCorner(int width, int height,
    int rows = CELL_ROW_COUNT, int columns = CELL_COLUMN_COUNT,
    TChannelStartCorner corner = CHANNEL_START_CORNER)
{
    Rect r;
    r.width = (width - 4) / (columns + 1) - 1;
    r.height = (height - 4) / (rows + 1) - 1;
    r.left = StartsRight(corner) ? width - 2 - r.width : 2;
    r.top = StartsBottom(corner) ? height - 2 - r.height : 2;
    return r;
}
// numberIndex는 화면 순서가 아니라 안내 번호-1이다. 항상 pUIx[0]/pUIy[0]이 1번.
inline Rect ColumnTitle(int numberIndex, int width, int height,
    int rows = CELL_ROW_COUNT, int columns = CELL_COLUMN_COUNT,
    TChannelStartCorner corner = CHANNEL_START_CORNER)
{
    const int column = StartsRight(corner) ? columns - 1 - numberIndex : numberIndex;
    Rect r = GridCell(0, column, width, height, true, rows, columns, corner);
    const Rect axis = AxisCorner(width, height, rows, columns, corner);
    r.top = axis.top;
    r.height = axis.height;
    return r;
}
inline Rect RowTitle(int numberIndex, int width, int height,
    int rows = CELL_ROW_COUNT, int columns = CELL_COLUMN_COUNT,
    TChannelStartCorner corner = CHANNEL_START_CORNER)
{
    const int row = StartsBottom(corner) ? rows - 1 - numberIndex : numberIndex;
    Rect r = GridCell(row, 0, width, height, true, rows, columns, corner);
    const Rect axis = AxisCorner(width, height, rows, columns, corner);
    r.left = axis.left;
    r.width = axis.width;
    return r;
}
inline Rect ForChannel(int index, int width, int height, bool axes)
{
    const Position p = ForIndex(index);
    return GridCell(p.row, p.column, width, height, axes);
}
}
#endif
