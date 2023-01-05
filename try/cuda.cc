#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>
#include "cublas_v2.h"

int main(int argc, char* argv[])
{
  // 所要時間測定用
  //timeval st,et;

  //ホスト側用
  float *hstA,*hstB,*hstC;

  //デバイス(GPU)側用 　
  float *devA,*devB,*devC;

  // 行列演算 C=αAB+βC のパラメータ
  float alpha = 1.0f;
  float beta = 0.0f;

  // 正方行列 A B C の 一辺のサイズ
  int num = 8192; //例

  //メモリサイズ算出
  int n2 = num*num;
  size_t memSz = n2 * sizeof(float);

//  //ホスト側メモリ確保
  hstA=(float*)malloc(memSz);
  hstB=(float*)malloc(memSz);
  hstC=(float*)malloc(memSz);

  // hstA,hstB に値を入れる。略

  // 計測開始点
  //gettimeofday(&st,NULL);
  
  //デバイス側メモリ確保
  cudaMalloc((void **)&devA,memSz);
  cudaMalloc((void **)&devB,memSz);
  cudaMalloc((void **)&devC,memSz);

  //ホスト → デバイス memcpy
  cublasSetVector(n2, sizeof(float), hstA, 1, devA, 1);
  cublasSetVector(n2, sizeof(float), hstB, 1, devB, 1);

  // デバイス側ハンドル作成
  cublasHandle_t handle;
  cublasCreate(&handle);

  // 行列の積 演算
  cublasSgemm(
	      handle,
	      CUBLAS_OP_N, //行列A 転置有無
	      CUBLAS_OP_N, //行列B 転置有無
	      num,    // 行列Aの行数
	      num,    // 行列Bの列数
	      num,    // 行列Aの列数(=行列Ｂの行数)
	      &alpha, // 行列の積に掛ける値(なければ1)
	      devA,   // 行列A
	      num,    // 行列Aの行数
	      devB,   // 行列B
	      num,    // 行列Bの行数
	      &beta,  // 行列Cに掛けるスカラ値(なければ0)
	      devC,   // 行列Cの初期値 兼 出力先
	      num // 行列Cの行数
	      );

  // デバイス側ハンドル破棄
  int status = cublasDestroy(handle);

  // ホスト ← デバイス memcpy (計算結果取得)
  cublasGetVector(n2, sizeof(float), devC, 1, hstC, 1);

  // デバイス側メモリ解放
  cudaFree(devA);
  cudaFree(devB);
  cudaFree(devC);

  // 計測終了点
  //gettimeofday(&et,NULL);

  // ホスト側メモリ解放
  free(hstA);
  free(hstB);
  free(hstC);

  
  printf("temp\n");
  return 0;
}
