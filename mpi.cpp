#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) //argc argüman sayısı, argv argümanlar char tipinde
{
    MPI_Init(&argc, &argv); //mpi başlatma
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    cout << "Process:" << rank << "/" << size <<endl; //0-1-2-3 ranklı processler sıraları karışık
    //AMAÇ: HER RAKAM KAÇ DEFA GEÇMİŞ?
    //bu diziyi birden fazla processe dağıtacağız her biri kendi parçasını hesaplayacak.
    //sonra bu parçaları birleştireceğiz
    //SCATTER-GATHER ile yapmaya karar verdim.

    int n = 10000;
    int data[n];
    if(rank == 0) //dizinin içini doldurma işlemleri rootta yapılır.
    {
        for(int i = 0; i < n; i++)
        {
            data[i] = rand() % 10; //rand rastgele büyük sayılar üretir modunu aldığımızda hep rakam kalır
        }

        for(int i = 0; i < n; i++)
            cout << data[i] << " ";
    }

    //dağıtım yapmadan önce her processin kaç elemanla uğraşacağını belirlememiz lazım.

    int local_n = n / size; //100 sayıyı 4 processe eşit dağıtırım.

    //her process kendi bölünmüş parçasını tutmak zorunda o yüzden local_n elemanlı dizi oluşturulur.

    int local_data[local_n];
    double start = MPI_Wtime(); //başlangıç zamanı
    MPI_Scatter(data, local_n, MPI_INT, local_data, local_n, MPI_INT, 0, MPI_COMM_WORLD);
            //PARAMETRELER: (100 elemanlı dizi, her processe giden eleman sayısı, gönderim veri tipi, processin veri alacağı buffer, her processin alacağı eleman sayısı,
            // alınacak veri tipi, dağıtımı yapacak process(rank=0), iletişim alanı)

    //bu işlem sonucu process 0 -> 25 eleman aldı process 1 -> 25 eleman aldı .....
    //şimdi her bir process kendi bölümünü hesaplamalı

    int const catg = 10; //0-9 arası rakamlar
    int local_part[catg] = {0}; //local_part[9] = 9 sayısı ne kadar geçti?

    for(int i = 0; i < local_n; i++)
    {
        int value = local_data[i]; //sayıyı alır ör: 9 sayısını aldı
        local_part[value]++; //saydırmak için kategoriye ekler. local_part[9] = 1 oldu
    }
    //artık her process kendi verisini saydırdı. artık her processten toplamları almalıyız.
    //mpi gather sayesinde root ile toplayalım

    int all_catg[size * catg]; //40 elemanlık bir dizi
    MPI_Gather(local_part, catg, MPI_INT, all_catg, catg, MPI_INT, 0, MPI_COMM_WORLD); //hepsinden sıklıkları topladık

    //şimdi root toplama yapacak
    if(rank == 0)
    {
        int global_catg[catg] = {0}; //global_catg[9] = tüm 9 sayısının toplamını tutar.
        for(int p = 0; p < size; p++) //her bir process
        {
            for(int x = 0; x < catg ; x++)
            {
                global_catg[x] += all_catg[p * catg + x]; //çarpım all_catg de o processin o kategorisinin toplamını veriyor
            }
        }

        cout << "Histogram: \n";
        for(int y = 0; y < catg; y++)
            cout <<  y << " icin:" <<  " : " << global_catg[y] << endl;

    }
    double end = MPI_Wtime(); //bitiş
    double time = end -start;

    if(rank == 0)
    {
        cout << size << " Process için toplam zaman: " << time << endl;
    }

    MPI_Finalize(); //mpiyi kapat
    return 0;
}

//macte derleme kodu: mpic++ mpi_histogram.cpp
//çalıştırma kodu: mpiexec -n 4 ./a.out