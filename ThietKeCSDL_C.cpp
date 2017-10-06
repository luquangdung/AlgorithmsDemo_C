#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<fstream>
#pragma warning(disable : 4996)

typedef struct ptham
{
	int vtrai[5];
	int ntrai = 0;
	int nphai = 0;
	int vphai[5];
};

typedef struct khoa
{
	int thuoctinh[20];
	int n_thuoctinh = 0;
};

typedef struct tapthuoctinh
{
	int thuoctinh[10];
	int n_thuoctinh = 0;
};

//------------------------- GỌI HÀM -------------------------//
void nhapMang(int mang[], int &n);
void nhapMang_2(int mang[], int &n);
void sapXepMang(int mang[], int n);
void hoanVi(int &a, int &b);
void xuatPTHam(ptham pth[], int sopt);
void nhapPTHam(ptham pth[], int &sopt);
void xuatMang(int mang[], int n);











//------------------------- ******* -------------------------//



void nhapMang(int mang[], int &n)
{
	printf("\n\nNhap so thuoc tinh cua tap thuoc tinh can tim bao dong : ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("Nhap pt thu %d : ", i);
		scanf("%d", &mang[i]);
	}
}

void nhapMang_2(int mang[], int &n)
{
	printf("\n\nNhap so thuoc tinh cua R : ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)	
		mang[i] = i + 1;	
}

void xuatMang(int mang[], int n)
{
	printf("\n-------------------- { ");
	for (int i = 0; i < n; i++)	
		printf("%d ", mang[i]);	
	printf("}");
}

void nhapPTHam(ptham pth[], int &sopt)
{
	printf("\n\nNhap so phu thuoc ham : ");
	scanf("%d", &sopt);
	for (int i = 0; i < sopt; i++)
	{
		printf("\nNhap phu thuoc ham %d :", i);
		printf("\nNhap so ptu ve trai : ");
		scanf("%d", &pth[i].ntrai);
		printf("\nNhap so ptu ve phai : ");
		scanf("%d", &pth[i].nphai);
		for (int j = 0; j < pth[i].ntrai; j++)
		{
			printf("\nNhap thuoc tinh %d cua ve trai trong phu thuoc ham %d : ", j, i);
			scanf("%d", &pth[i].vtrai[j]);
		}
		for (int j = 0; j < pth[i].nphai; j++)
		{
			printf("\nNhap thuoc tinh %d cua ve phai trong phu thuoc ham %d : ", j, i);
			scanf("%d", &pth[i].vphai[j]);
		}
	}
}

void xuatPTHam(ptham pth[], int sopt)
{
	printf("\n\nF : ");
	printf("\n-------------------- {");
	for (int i = 0; i < sopt; i++)
	{
		for (int j = 0; j < pth[i].ntrai; j++)
		{
			printf("%d", pth[i].vtrai[j]);
		}
		printf("->");
		for (int j = 0; j < pth[i].nphai; j++)
		{
			printf("%d", pth[i].vphai[j]);
		}
		if (i != sopt - 1)
			printf(", ");
	}
	printf("}");
}

void hoanVi(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void sapXepMang(int mang[], int n)
{
	for (int i = 0; i < n - 1; i++)	
		for (int j = i + 1; j < n; j++)		
			if (mang[i] > mang[j])
				hoanVi(mang[i], mang[j]);
}

void xoaPTTheoViTri(int mang[], int &n, int vt)
{
	for (int i = vt; i < n; i++)	
		hoanVi(mang[i], mang[i + 1]);	
	n--;
}

void xoaPTTrung(int mang[], int &n)
{
	sapXepMang(mang, n);
	int i = 0;
	while (i < n - 1)
	{
		if (mang[i] == mang[i + 1])
		{
			xoaPTTheoViTri(mang, n, i + 1);
			i = 0;
		}
		else
			i++;
	}
}

//true : còn tồn tại
//false : không còn tồn tại
bool kiemTraTonTai(int mang[], int n, int x)
{
	for (int i = 0; i < n; i++)
		if (mang[i] == x)
			return true;
	return false;
}

void themPTu(int mang[], int &n, int x)
{
	n++;
	mang[n - 1] = x;
}

//true : mangcon tồn tại trong mangcha
//false : mangcon không tồn tại trong mangcha
bool kiemTraMang_TonTai_Mang(int mangcha[], int mangcon[], int ncha, int ncon)
{
	if (ncon > ncha)
		return false;
	else
	{
		for (int i = 0; i < ncon; i++)
			if (kiemTraTonTai(mangcha, ncha, mangcon[i]) == false)
				return false;
		return true;
	}
}

//true : 2 mảng trùng nhau
//false : 2 mảng không trùng nhau
bool kiemTraMangTrung(int mang1[], int mang2[], int n1, int n2)
{
	if (n1 == n2)
	{
		sapXepMang(mang1, n1);
		sapXepMang(mang2, n2);
		for (int i = 0; i < n1; i++)
			if (mang1[i] != mang2[i])
				return false;
		return true;
	}
	else
		return false;
}

void timBaoDong(ptham pth[], int sopt_pth, int r[], int n_r, int thuoctinh[], int &n_thuoctinh, int &n_baodong, int bao_dong[])
{
	n_baodong = 0;

	//Thêm vào bao đóng tập thuộc tính ban đầu
	for (int i = 0; i < n_thuoctinh; i++)	
		themPTu(bao_dong, n_baodong, thuoctinh[i]);	

	int i = 0;
	while( i < sopt_pth)
	{
		//Nếu vế trái của phụ thuộc hàm là con của bao đóng thì thêm vế phải của phụ thuộc hàm vào bao đóng
		//Ngược lại, duyệt phụ thuộc hàm tiếp theo
		if (kiemTraMang_TonTai_Mang(bao_dong, pth[i].vtrai, n_baodong, pth[i].ntrai) == true)
		{
			//Lưu số thuộc tính của bao đóng trước khi thêm
			int temp = n_baodong;
			for (int j = 0; j < pth[i].nphai; j++)			
				if (kiemTraTonTai(bao_dong, n_baodong, pth[i].vphai[j]) == false)
					themPTu(bao_dong, n_baodong, pth[i].vphai[j]);			
			sapXepMang(bao_dong, n_baodong);

			//Nếu temp != n_baodong thì bao đóng có phần tử được thêm nên duyệt lại từ đầu phuộc thuộc hàm
			//Ngược lại, duyệt phụ thuộc hàm tiếp theo
			if (temp != n_baodong)
				i = 0;
			else
				i++;

			//Nếu bao đóng == R thì dừng
			if (kiemTraMangTrung(r, bao_dong, n_r, n_baodong) == true)
				break;
		}
		else
			i++;
	}
}

void chepMang(int mang[], int copy[], int n_mang)
{
	for (int i = 0; i < n_mang; i++)
		copy[i] = mang[i];
}

void timKhoa(ptham pth[], int n_pth, int r[], int n_r, int khoa[], int &n_khoa)
{
	//Mảng bao đóng
	int baodong[10];
	int n_baodong = 0;

	//Mảng trạng thái trước khi loại thuộc tính
	int redo[10];
	int n_redo = 0;
	
	n_khoa = n_r;

	//Khoá tạm thời chứa tất cả thuộc tính của R
	chepMang(r, khoa, n_r);

	//Duyệt ngược
	int i = n_khoa - 1;
	while (i >= 0)
	{
		//Mảng redo lưu trạng thái khoá trước khi loại thuộc tính
		chepMang(khoa, redo, n_khoa);
		n_redo = n_khoa;
		printf("\n\nLoai %d : ", khoa[i]);

		//Loại 1 thuộc tính từ khoá tạm thời
		xoaPTTheoViTri(khoa, n_khoa, i);
		printf("\nSau khi loai : ");
		xuatMang(khoa, n_khoa);

		//Tìm bao đóng của khoá
		timBaoDong(pth, n_pth, r, n_r, khoa, n_khoa, n_baodong, baodong);
		printf("\nBao dong :");
		xuatMang(baodong, n_baodong);

		//Nếu bao đóng của khoá không bằng U => Khoá trở về trạng thái trước khi xoá (khoá = redo)
		if (kiemTraMangTrung(r, baodong, n_r, n_baodong) == false)
		{
			printf("\nBao dong != U");
			printf("\n=> Khong loai");
			chepMang(redo, khoa, n_redo);
			printf("\n=> Khoa : ");
			xuatMang(redo, n_redo);
			n_khoa = n_redo;
		}
		//Ngược lại => Khoá = khoá sau khi loại thuộc tính
		else
		{
			printf("\nBao dong == U");
			printf("\n=> Khoa : ");
			xuatMang(khoa, n_khoa);
		}
		i--;
	}
}

void taoMang_TraiPhai(ptham pth[], int sopt, int mangtrai[], int mangphai[], int &n_mangtrai, int &n_mangphai)
{
	for (int i = 0; i < sopt; i++)
	{
		for (int j = 0; j < pth[i].ntrai; j++)
			themPTu(mangtrai, n_mangtrai, pth[i].vtrai[j]);
		for (int j = 0; j < pth[i].nphai; j++)
			themPTu(mangphai, n_mangphai, pth[i].vphai[j]);
	}
}

void timTrungGian(ptham pth[], int sopt, int mangphai[], int &n_mphai, int trgian[], int &n_trgian)
{
	int mangtrai[10];
	int n_mtrai = 0;

	taoMang_TraiPhai(pth, sopt, mangtrai, mangphai, n_mtrai, n_mphai);

	for (int i = 0; i < n_mtrai; i++)
		for (int j = 0; j < n_mphai; j++)
			if (i != j && mangtrai[i] == mangphai[j])
				themPTu(trgian, n_trgian, mangtrai[i]);
}

void timNguon(ptham pth[], int sopt, int mang[], int n, int trgian[], int n_trgian, int mangphai[], int n_mphai, int nguon[], int &n_nguon)
{
	chepMang(mang, nguon, n);
	n_nguon = n;

	int i = 0;
	while (i < n_nguon)
	{
		if (kiemTraTonTai(mangphai, n_mphai, nguon[i]) == true || kiemTraTonTai(trgian, n_trgian, nguon[i]) == true)
		{
			xoaPTTheoViTri(nguon, n_nguon, i);
			i = 0;
		}
		else
			i++;
	}
}

void xuat(ptham pth[], int sopt, int mang[], int n)
{
	printf("\nR : ");
	xuatMang(mang, n);
	xuatPTHam(pth, sopt);
}

void timXi(int trgian[], int n_trgian, tapthuoctinh t[], int &n_t)
{
	n_t = 0;
	for (int i = 0; i < n_trgian - 1; i++)
	{
		themPTu(t[n_t].thuoctinh, t[n_t].n_thuoctinh, trgian[i]);
		for (int j = i; j < n_trgian - 1; j++)
		{
			n_t++;
			for (int k = i; k <= j + 1; k++)			
				themPTu(t[n_t].thuoctinh, t[n_t].n_thuoctinh, trgian[k]);
		}
		n_t++;
	}
	printf("\n%d", n_t);
}

void xuatTapThuocTinh(tapthuoctinh t[], int n_t)
{
	for (int i = 0; i < n_t; i++)	
		xuatMang(t[i].thuoctinh, t[i].n_thuoctinh);
}


























void thucThi()
{
	int chon;
	ptham pth[10];
	int sopt = 0;
	int n = 0;
	int mang[10];
	int baodong[10];
	nhapMang_2(mang, n);
	printf("\nR : ");
	xuatMang(mang, n);
	nhapPTHam(pth, sopt);
	xuatPTHam(pth, sopt);
	printf("\nR : ");
	xuatMang(mang, n);
	do
	{
		printf("\n1 : Tim bao dong\n2 : Tim mot khoa\n3 : Tim khoa theo do thi\n4 : Tim tat ca khoa\n5 : Thoat");
		printf("\n\nNhap lua chon : ");
		scanf("%d", &chon);
		switch (chon)
		{
		case 1:
		{
			printf("\n....................... TIM BAO DONG .......................");
			int thuoctinh[10];
			int n_thuoctinh = 0;
			int n_baodong = 0;

			xuat(pth, sopt, mang, n);
			nhapMang(thuoctinh, n_thuoctinh);
			timBaoDong(pth, sopt, mang, n, thuoctinh, n_thuoctinh, n_baodong, baodong);
			printf("\n\nBao dong : ");
			xuatMang(baodong, n_baodong);;
			printf("\n\n\n\n");
			break;
		}
		case 2:
		{
			printf("\n....................... TIM KHOA .......................");
			int khoa[10];
			int n_khoa = 0;
			int n_baodong = 0;

			xuat(pth, sopt, mang, n);
			timKhoa(pth, sopt, mang, n, khoa, n_khoa);
			printf("\n\nKhoa cua R : ");
			xuatMang(khoa, n_khoa);
			printf("\n\n\n\n");
			break;
		}
		case 4:
		{
			printf("\n....................... TIM TAT CA KHOA .......................");
			int trgian[10];
			int n_trgian = 0;
			int mangphai[10];
			int n_mphai = 0;
			int nguon[10];
			int n_nguon = 0;

			tapthuoctinh t[10];
			int n_t = 0;

			xuat(pth, sopt, mang, n);
			timTrungGian(pth, sopt,mangphai, n_mphai, trgian, n_trgian);
			timNguon(pth, sopt, mang, n, trgian, n_trgian, mangphai, n_mphai, nguon, n_nguon);
			printf("\n\nTap nguon : ");
			xuatMang(nguon, n_nguon);
			printf("\n\nTap trung gian : ");
			xuatMang(trgian, n_trgian);
			printf("\n\n\n\n");
			break;
		}
		case 3:
		{
			break;
		}
		}
	} while (chon < 5);
}







void main()
{
	thucThi();
	getch();
}