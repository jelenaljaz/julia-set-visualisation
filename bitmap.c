#include <stdio.h>
#include <windows.h>
#include "bitmap.h"

void saveToFile(BYTE* pBitmapBits, LONG lWidth, LONG lHeight, WORD wBitsPerPixel, LPCTSTR lpszFileName)
{
    RGBQUAD palette[256];
    BITMAPINFOHEADER bitmapInfoHeader = {0};
    BITMAPFILEHEADER bitmapFileHeader = {0};
    HANDLE hFile;
    DWORD dwWritten = 0;

    int i, j;

    for (i = 0; i < 256; ++i)
    {
        palette[i].rgbRed = i;
        palette[i].rgbGreen = (i * 2) % 256;
        palette[i].rgbBlue = (i * 3) % 256;
    }

    bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfoHeader.biBitCount = wBitsPerPixel;
    bitmapInfoHeader.biClrImportant = 0;
    bitmapInfoHeader.biClrUsed = 0;
    bitmapInfoHeader.biCompression = BI_RGB;
    bitmapInfoHeader.biHeight = lHeight;
    bitmapInfoHeader.biWidth = lWidth;
    bitmapInfoHeader.biPlanes = 1;
    bitmapInfoHeader.biSizeImage = lWidth * lWidth * (wBitsPerPixel / 8);

    bitmapFileHeader.bfType = 'B' + ('M' << 8);
    bitmapFileHeader.bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) * 256;
    bitmapFileHeader.bfSize = bitmapFileHeader.bfOffBits + bitmapInfoHeader.biSizeImage;

    hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (!hFile) { return; }

    WriteFile(hFile, &bitmapFileHeader, sizeof(bitmapFileHeader), &dwWritten, NULL);
    WriteFile(hFile, &bitmapInfoHeader, sizeof(bitmapInfoHeader), &dwWritten, NULL);
    WriteFile(hFile, &palette[0], sizeof(RGBQUAD) * 256, &dwWritten, NULL);

    if (lWidth % 4 == 0)
    {
        WriteFile(hFile, pBitmapBits, bitmapInfoHeader.biSizeImage, &dwWritten, NULL);
    }
    else
    {
        char empty [4 - lWidth % 4];
        for (j = 0; j < lHeight; ++j)
        {
            WriteFile(hFile, &pBitmapBits[j * lWidth], lWidth, &dwWritten, NULL);
            WriteFile(hFile, empty, 4 - lWidth % 4, &dwWritten, NULL);
        }
    }

    CloseHandle(hFile);
}

void bmpOut(unsigned char picture[][DIM], const char* filename)
{
    BYTE* img = (BYTE*) picture[0];
    WCHAR tmpstr[256];
    MultiByteToWideChar(0, 0, filename, -1, tmpstr, 256);

    int nUserNameLenUnicode = lstrlenW(tmpstr);
    int nUserNameLen = WideCharToMultiByte(CP_ACP, 0, tmpstr, nUserNameLenUnicode, NULL, 0, NULL, NULL);
    char pszUserName [nUserNameLen];
    WideCharToMultiByte(CP_ACP, 0, tmpstr, nUserNameLenUnicode, pszUserName, nUserNameLen, NULL, NULL);

    saveToFile(img, DIM, DIM, 8, pszUserName);
}