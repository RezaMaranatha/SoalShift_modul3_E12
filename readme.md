# Soal Shift Modul 3 E12
by:<br/> 
I Dewa Putu Wiprah A      (05111740000152)<br/>
Reza Adipatria Maranatha  (05111740000186)
# 1
Soal satu meminta kita untuk menghitung nilai faktorial dari suatu variable yang di input saat memanggil program (bash) dengan memasukkan argumen ke dalam main, lalu diubah dari yang awal bertipe data char menjadi integer dengan fungsi atoi. Lalu di sort dengan menggunakan fungsi qsort secara ascending. Lalu memanggil thread yang akan menghitung hasil faktorial dari setiap input
# 2
Untuk mengerjakan soal nomor 2, kita membuat 2 server dan 2 client. Server Pembeli berfungsi untuk membeli barang, server ini menggunakan shared memory untuk menampilkan jumlah stok. Server Penjual berfungsi untuk menambah stok barang, server penjual memiliki 2 fungsi yaitu : menampilkan stok saat ini setiap 5 detik sekali, dan satunya untuk menambah jumlah stok saat ini, untuk menampilkan stok, digunakan thread. 
# 3
Soal tiga meminta kita membuat tiga fitur, yaitu "All Status" untuk menampilkan WakeUp_Status dan Spirit_Status, "Agmal Ayo Bangun" untuk menambah point WakeUp_Status sebanyak 15, dan "Iraj Ayo Tidur" mengurangi point Spirit_Status sebanyak 20. Lalu thread dibuat untuk melaksanakan semua fitur tersebut. Lalu ada kasus khusus dimana jika fitur "Agmal Ayo Bangun" sudah dijalankan 3 kali, maka fitur "Iraj Ayo Tidur" akan diblokir selama 10 detik, begitu pula sebaliknya. Program akan berhenti saat WakeUp_Status <= 0 atau Spirit_Status <=0
# 4
Untuk mengerjakan soal nomor 4 kita membuat 6 thread, 2 thread untuk menyimpan proses dalam file.txt, kemudian 2 thread untuk mengkompres file .txt menjadi .zip dan men-delete file .txt tsb, kemudian 2 thread terakhir digunakan untuk meng-unzip file .zip tersebut. di fungsi main digunakan untuk menjalankan semua threadnya dan membuat 2 folder yang diminta. 
# 5
Soal nomor lima meminta kita untuk membuat sebuah game dimana kita memelihara monster, monster tersebut dapat diberi makan untuk menambah status hunger (selama masih ada stok makanan), lalu dimandikan untuk menaikan status hygiene, lalu batttle untuk melawan NPC, shop untuk membeli persediaan makanan, dan exit untuk keluar dari permainan. Health akan bertambah sebanyak 5 setiap 10 detik dan hunger akan berkurang sebanyak 5 setiap 10 detik, lalu hygiene akan berkurang setiap 30 detik. Fitur "bath" akan cooldown selama 20 detik setelah digunakan, dan menampilkan waktu cooldown remaining pada standby mode.
