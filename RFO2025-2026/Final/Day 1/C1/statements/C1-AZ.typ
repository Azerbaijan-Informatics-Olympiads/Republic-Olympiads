// ready

#import "/templateDay1-AZ.typ": *

#show: project.with(
  title: "Nizamlı Bağ",
  time_limit: 2,
  memory_limit: 512
)

Rəsul adlı bir bağban $N$ ağacdan ibarət bir sıraya qulluq edir. Hər bir ağacın mövcud hündürlüyü bir tam ədədlə ifadə olunur. 

Bağın gözəlliyini qorumaq üçün qəti bir qayda var: heç bir ağacın $K$ hündürlüyünə çatmasına icazə verilmir. Nə vaxt bir ağac tam olaraq $K$ hündürlüyünə çatarsa, Rəsul dərhal onu kəsir və hündürlüyünü $0$-a endirir.

Hər hansı yanaşı ağac cütü üçün, əgər sol ağacın hündürlüyü sağ ağacın hündürlüyündən ciddi kiçikdirsə, Rəsul bu yanaşı ağac cütünü *Nizamlı* hesab edir. Daha dəqiq desək:
#align(center)[$A_i < A_(i+1)$ şərti ödənilməlidir.]

Növbəti $Q$ gün ərzində Rəsul bağda əməliyyatlar icra edəcək və müşahidələr aparacaq. Hər gün aşağıdakı iki hadisədən biri baş verir:
- #box[*`1 L R`*]: Rəsul $L$-dən $R$-ə qədər (hər ikisi daxil) olan ağacları sulayır #box[($1 <= L <= R <= N$). $L <= i <= R$] şərtini ödəyən hər bir $i$ üçün ağacın hündürlüyü #box[$(A_i + 1) mod K$] olaraq dəyişir.
- #box[*`2 L R`*]: Rəsul $L$-dən $R$-ə qədər (hər ikisi daxil) olan aralıqdakı Nizamlı cütlüklərin sayını hesablayır #box[($1 <= L <= R <= N$)].

Ağacların ilkin hündürlükləri və hadisələr ardıcıllığı verildikdə, Rəsula sorğulara cavab verməkdə kömək edin.

_Qeyd: #box[$(A_i + 1) mod K$] ifadəsində $mod$, qalıq əməliyyatını bildirir._

== Giriş

Girişin birinci sətrində üç tam ədəd $N$, $Q$ və $K$ #box[($1 <= N, Q <= 2 times 10^5$, $2 <= K <= 10$)] — ağacların sayı, günlərin sayı və hündürlük limiti verilir.

İkinci sətirdə ağacların ilkin hündürlüyünü ifadə edən $N$ tam ədəd #box[$A_1, A_2, ..., A_N$ ($0 <= A_i < K$)] verilir.

Növbəti $Q$ sətrin hər biri bir hadisəni təsvir edir. Hadisələr #box[`1 L R`] və ya #box[`2 L R`] #box[($1 <= L <= R <= N$)] formatındadır.


== Çıxış

2-ci növ hər bir hadisə üçün yeni sətirdə tək bir tam ədəd çıxışa verin: #box[$L <= i < R$] və #box[$A_i < A_(i+1)$] şərtlərini ödəyən $i$ indekslərinin sayı. 

_(Qeyd: Cütlük yalnız hər iki ağac verilmiş aralığın içində olduqda hesablana bilər. Yəni, cütlük Nizamlı olsa belə, #box[$(R, R+1)$] cütlüyü hesaba alınmır)._

#pagebreak()

== Məhdudiyyətlər

- $1 <= N, Q <= 2 times 10^5$
- $2 <= K <= 10$
- $0 <= A_i < K$
- $1 <= L<=R<=N$
- alt tapşırıqlar üçün qiymətləndirmə bölməsinə baxın.

== Nümunələr

// Input, Output, Explanation
#let examples = (
  (
  "6 6 3
1 2 0 1 2 1
2 1 6
1 2 4
2 2 5
1 5 6
2 1 6
2 3 3
",
  
  "3
2
3
0",

[Ağacaların ilkin hündürlükləri: #box[`[1, 2, 0, 1, 2, 1]`]. 
- *1-ci hadisə (Aralıq 1-6):* Bütün sıranı yoxlayırıq. Nizamlı cütlüklər (1,2), (3,4) və (4,5) indekslərindədir. Cavab *3*-dür.
- *2-ci hadisə (Aralıq 2-4):* 2, 3 və 4-cü ağaclar sulanır. Ağacların boyu #box[`[1, 0, 1, 2, 2, 1]`] olur. (Diqqət edin: 2-ci ağac $K=3$ limitinə çatdığı üçün kəsilərək 0 oldu).
- *3-cü hadisə (Aralıq 2-5):* Alt massiv #box[`[0, 1, 2, 2]`]-dir. Nizamlı cütlüklər #box[`0 < 1`] və #box[`1 < 2`]-dir. Cavab *2*-dir.
- *4-cü hadisə (Aralıq 5-6):* 5 və 6-cı ağaclar sulanır. Sıra #box[`[1, 0, 1, 2, 0, 2]`] olur.
- *5-ci hadisə (Aralıq 1-6):* Bütün aralığı yoxlayırıq. Nizamlı cütlüklər (2,3), (3,4) və (5,6) indekslərindədir. Cavab *3*-dür.
- *6-cı hadisə (Aralıq 3-3):* Bu aralıqda hər hansı cütlük yoxdur, ona görə cavab *0*-dır.
]
  ),
)

#table(
  columns: (auto, auto, 1fr),
  [*Giriş*], [*Çıxış*], [*İzah*],
  ..examples.map(
    example => (text(example.at(0), font: "Cascadia Code"), text(example.at(1), font: "Cascadia Code"), example.at(2)) 
  ).flatten()
)

== Qiymətləndirmə

Bu məsələ aşağıdakı kimi $5$ alt tapşırıqdan ibarətdir:

#table(
  align: center,
  columns: (auto, 1fr, 1fr),
  [*Alt tapşırıq*], [*Əlavə məhdudiyyətlər*], [*Bal*],
  [0], [Nümunələr], [0 bal],
  [1], [$N, Q <= 1000$], [10 bal],
  [2], [1-ci növ hadisə yoxdur], [15 bal],
  [3], [Bütün 1-ci növ hadisələrdə $L = R$], [20 bal],
  [4], [$K = 2$], [25 bal],
  [5], [Əlavə məhdudiyyət yoxdur], [30 bal]
)