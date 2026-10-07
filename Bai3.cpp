#include <stdio.h>
#include <string.h>

#define MAX_VE 100

typedef struct {
    char maVe[16];
    char tenHanhKhach[51];
    char hangVe[21];
    float canNangHanhLy;
    double cuocHanhLy;
} VeMayBay;

void xoaKyTuXuongDong(char str[]) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    VeMayBay danhSachVe[MAX_VE];
    int soLuong = 0;
    
    printf("Nhap so luong ve may bay: ");
    if (scanf("%d", &soLuong) != 1 || soLuong < 1 || soLuong > 100) {
        printf("Loi: So luong ve khong hop le!\n");
        return 0;
    }
    while (getchar() != '\n');

    for (int i = 0; i < soLuong; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);
        
        printf("Ma ve PNR: ");
        fgets(danhSachVe[i].maVe, sizeof(danhSachVe[i].maVe), stdin);
        xoaKyTuXuongDong(danhSachVe[i].maVe);

        printf("Ho ten hanh khach: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        xoaKyTuXuongDong(danhSachVe[i].tenHanhKhach);

        printf("Hang ve (Business/Deluxe/Eco): ");
        fgets(danhSachVe[i].hangVe, sizeof(danhSachVe[i].hangVe), stdin);
        xoaKyTuXuongDong(danhSachVe[i].hangVe);

        do {
            printf("Khoi luong hanh ly ky gui (kg): ");
            if (scanf("%f", &danhSachVe[i].canNangHanhLy) != 1 || danhSachVe[i].canNangHanhLy < 0) {
                printf("Loi: Can nang hanh ly phai la so khong am. Vui long nhap lai!\n");
                while (getchar() != '\n');
                danhSachVe[i].canNangHanhLy = -1;
            } else {
                while (getchar() != '\n');
            }
        } while (danhSachVe[i].canNangHanhLy < 0);

        if (strcasecmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20.0) {
                danhSachVe[i].cuocHanhLy = 0;
            } else {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20.0) * 50000;
            }
        } else {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000;
        }
    }

    double tongTien = 0;
    int maxIndex = 0;
    for (int i = 0; i < soLuong; i++) {
        tongTien += danhSachVe[i].cuocHanhLy;
        if (danhSachVe[i].canNangHanhLy > danhSachVe[maxIndex].canNangHanhLy) {
            maxIndex = i;
        }
    }

    printf("\n================================== DANH SACH VE MAY BAY CHUYEN BAY ==================================\n");
    printf("%-4s %-12s %-25s %-12s %12s %15s\n", "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < soLuong; i++) {
        printf("%-4d %-12s %-25s %-12s %12.1f %15.0f\n", 
            i + 1, 
            danhSachVe[i].maVe, 
            danhSachVe[i].tenHanhKhach, 
            danhSachVe[i].hangVe, 
            danhSachVe[i].canNangHanhLy, 
            danhSachVe[i].cuocHanhLy);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tong tien cuoc hanh ly toan chuyen: %.0f VND\n", tongTien);
    printf("Ve co hanh ly ky gui nang nhat: %s - %s (%.1f kg)\n", 
        danhSachVe[maxIndex].maVe, 
        danhSachVe[maxIndex].tenHanhKhach, 
        danhSachVe[maxIndex].canNangHanhLy);

    char maCapNhat[16];
    printf("\nNhap ma ve PNR can cap nhat hanh ly: ");
    fgets(maCapNhat, sizeof(maCapNhat), stdin);
    xoaKyTuXuongDong(maCapNhat);

    int foundIndex = -1;
    for (int i = 0; i < soLuong; i++) {
        if (strcmp(danhSachVe[i].maVe, maCapNhat) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Khong tim thay ma ve PNR nay trong he thong!\n");
    } else {
        float canNangMoi;
        do {
            printf("Nhap can nang hanh ly ky gui moi (kg): ");
            if (scanf("%f", &canNangMoi) != 1 || canNangMoi < 0) {
                printf("Loi: Can nang hanh ly phai la so khong am. Vui long nhap lai!\n");
                while (getchar() != '\n');
                canNangMoi = -1;
            } else {
                while (getchar() != '\n');
            }
        } while (canNangMoi < 0);

        danhSachVe[foundIndex].canNangHanhLy = canNangMoi;
        if (strcasecmp(danhSachVe[foundIndex].hangVe, "Business") == 0) {
            if (danhSachVe[foundIndex].canNangHanhLy <= 20.0) {
                danhSachVe[foundIndex].cuocHanhLy = 0;
            } else {
                danhSachVe[foundIndex].cuocHanhLy = (danhSachVe[foundIndex].canNangHanhLy - 20.0) * 50000;
            }
        } else {
            danhSachVe[foundIndex].cuocHanhLy = danhSachVe[foundIndex].canNangHanhLy * 50000;
        }

        printf("\n--- CAP NHAT THONG TIN HANH LY ---\n");
        printf("Tim thay ma ve %s. Da cap nhat cuoc hanh ly moi: %.0f VND.\n", 
            danhSachVe[foundIndex].maVe, danhSachVe[foundIndex].cuocHanhLy);

        tongTien = 0;
        maxIndex = 0;
        for (int i = 0; i < soLuong; i++) {
            tongTien += danhSachVe[i].cuocHanhLy;
            if (danhSachVe[i].canNangHanhLy > danhSachVe[maxIndex].canNangHanhLy) {
                maxIndex = i;
            }
        }

        printf("\n================================ DANH SACH VE MAY BAY SAU CAP NHAT ================================\n");
        printf("%-4s %-12s %-25s %-12s %12s %15s\n", "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
        printf("----------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < soLuong; i++) {
            printf("%-4d %-12s %-25s %-12s %12.1f %15.0f\n", 
                i + 1, 
                danhSachVe[i].maVe, 
                danhSachVe[i].tenHanhKhach, 
                danhSachVe[i].hangVe, 
                danhSachVe[i].canNangHanhLy, 
                danhSachVe[i].cuocHanhLy);
        }
        printf("----------------------------------------------------------------------------------------------------\n");
        printf("Tong tien cuoc hanh ly toan chuyen: %.0f VND\n", tongTien);
        printf("Ve co hanh ly ky gui nang nhat: %s - %s (%.1f kg)\n", 
            danhSachVe[maxIndex].maVe, 
            danhSachVe[maxIndex].tenHanhKhach, 
            danhSachVe[maxIndex].canNangHanhLy);
    }

    return 0;
}
