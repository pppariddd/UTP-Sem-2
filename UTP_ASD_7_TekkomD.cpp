#include <iostream>
using namespace std;

struct Mahasiswa{
    string nama;
    int kelompok;
    Mahasiswa *next;
};

// tahapan proses
Mahasiswa *waitingHead = NULL; 
Mahasiswa *waitingTail = NULL;
Mahasiswa *ongoingHead = NULL;
Mahasiswa *finishedHead = NULL;

// buat node
Mahasiswa *createNode(string nama, int kelompok){
    Mahasiswa *node = new Mahasiswa;
    node->nama = nama;
    node->kelompok = kelompok;
    node->next = NULL;
    return node;
}

// waiting
void tambahWaiting(string nama, int kelompok){
    Mahasiswa *node = createNode(nama, kelompok);
    if (waitingHead == NULL){
        waitingHead = waitingTail = node;
    }
    else{
        waitingTail->next = node;
        waitingTail = node;
    }
}

// ongoing
void insertOngoing(Mahasiswa *node){
    if (ongoingHead == NULL || node->kelompok < ongoingHead->kelompok){
        node->next = ongoingHead;
        ongoingHead = node;
    }
    else{
        Mahasiswa *temp = ongoingHead;
        while (temp->next != NULL && temp->next->kelompok <= node->kelompok)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
}

// mulai praktikum
void mulaiPraktikum(){
    if (waitingHead == NULL){
        cout << "Waiting list kosong!\n";
        return;
    }

    Mahasiswa *pindah = waitingHead;
    waitingHead = waitingHead->next;

    if (waitingHead == NULL)
        waitingTail = NULL;

    pindah->next = NULL;
    insertOngoing(pindah);

    cout << "Mahasiswa dipindahkan ke On-Going.\n";
}

// selesai praktikum
void selesaiPraktikum(int kelompok){
    if (ongoingHead == NULL){
        cout << "On-Going kosong!\n";
        return;
    }

    Mahasiswa *temp = ongoingHead, *prev = NULL;

    while (temp != NULL){
        if (temp->kelompok == kelompok)
        {
            Mahasiswa *hapus = temp;

            if (prev == NULL)
            {
                ongoingHead = temp->next;
                temp = ongoingHead;
            }
            else
            {
                prev->next = temp->next;
                temp = temp->next;
            }

            // masuk ke finished (di depan)
            hapus->next = finishedHead;
            finishedHead = hapus;
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }

    cout << "Kelompok selesai dipindahkan ke Finished.\n";
}

// tampilkan
void tampil(Mahasiswa *head){
    if (head == NULL){
        cout << "Kosong\n";
        return;
    }

    Mahasiswa *temp = head;
    while (temp != NULL){
        cout << temp->nama << " (Kel: " << temp->kelompok << ") -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

// list pilihan menu
int main(){
    int pilihan;
    string nama;
    int kelompok;

    do{
        cout << "\n=== SISTEM PRAKTIKUM ===\n";
        cout << "1. Tambah Mahasiswa\n";
        cout << "2. Mulai Praktikum\n";
        cout << "3. Selesaikan Kelompok\n";
        cout << "4. Tampilkan Data\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan){
        case 1:
            cout << "Nama: ";
            cin >> nama;
            cout << "Kelompok: ";
            cin >> kelompok;
            tambahWaiting(nama, kelompok);
            break;

        case 2:
            mulaiPraktikum();
            break;

        case 3:
            cout << "Masukkan nomor kelompok: ";
            cin >> kelompok;
            selesaiPraktikum(kelompok);
            break;

        case 4:
            cout << "=============================" << endl;
            cout << "\nWaiting List:\n";
            tampil(waitingHead);
            cout << "=============================" << endl;
            cout << "\nOn-Going List:\n";
            tampil(ongoingHead);
            cout << "=============================" << endl;
            cout << "\nFinished List:\n";
            tampil(finishedHead);
            break;
        }
    } while (pilihan != 0);

    return 0;
}