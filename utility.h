#pragma once

bool isWhite(char c)
{
    return c == ' ' || c == '\n' || c == '\n';
}

bool isNumber(char c)
{
    return ((c >= '0') && (c <= '9')) || c == '-';
}