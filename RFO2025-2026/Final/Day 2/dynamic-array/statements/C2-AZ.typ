// ready

#import "/templateDay2-AZ.typ": *

#show: project.with(
  title: "Dinamik Massiv 2",
  time_limit: 1,
  memory_limit: 256
)

Müəllim lövhəyə $a_1, a_2, dots, a_n$ ədədlərini yazır. Daha sonra, lövhədə yazılan ədədlərin sayı $m$-ə çatana qədər, şagirdlər bir-bir lövhəyə yaxınlaşır, hazırda lövhədə yazılmış istənilən iki ardıcıl ədədi seçir və bu iki ədədin cəmini onların arasına yazır.

Bu dəfə müəllim lövhədə yazılmış ən böyük ədədin mümkün olan ən kiçik qiymətini deyil _(bu 2024-cü ilin yarımfinal məsələsində soruşulurdu)_, lövhədə alınan dəqiq ardıcıllığı öyrənmək istəyir.

Müəyyən edin ki, lövhədəki ədədlərin ümumi sayı $m$ olduqda, ardıcıllıq tam olaraq $b_1, b_2, dots, b_m$ ola bilərmi.

== Giriş
Birinci sətirdə iki tam ədəd $n$ və $m$ ($1 <= n, m <= 10^5$) verilir.

İkinci sətirdə $n$ müsbət tam ədəd $a_1, a_2, dots, a_n$ ($1 <= a_i <= 10^9$) verilir.

Üçüncü sətirdə $m$ müsbət tam ədəd $b_1, b_2, dots, b_m$ ($1 <= b_i <= 10^9$) verilir.

== Çıxış
Əgər $a$ massivindən $b$ massivini almaq mümkündürsə, `YES`, əks halda, `NO` çap edin.

== Məhdudiyyətlər

- $1 <= n, m <= 10^5$
- $1 <= a_i <= 10^9$
- $1 <= b_i <= 10^9$
- alt tapşırıqlar üçün qiymətləndirmə bölməsinə baxın.

== Nümunələr

// Input, Output, Explanation
#let examples = (
  (
  "4 9
1 3 3 4
1 4 11 7 3 6 9 3 4",

  "YES",

  [$a=[1, 3, 3, 4] arrow.double [1, #text(fill: red)[4], 3, 3, 4] arrow.double [1, 4, #text(fill: red)[7], 3, 3, 4] arrow.double [1, 4, #text(fill: red)[11], 7, 3, 3, 4] arrow.double [1, 4, 11, 7, 3, #text(fill: red)[6], 3, 4] arrow.double [1, 4, 11, 7, 3, 6, #text(fill: red)[9], 3, 4] = b$]
  ),
  (
  "4 5
2 6 4 1
2 6 4 5 1",

  "YES",

  [Başlanğıcda $a = [2, 6, 4, 1]$.

Üçüncü və dördüncü elementlər arasında əməliyyat tətbiq olunur və $4 + 1 = 5$ əlavə edilir.

Alınan massiv $b$ ilə eynidir.]
  ),
  (
  "4 3
1 2 3 4
1 2 3",

  "NO",

  [Hər əməliyyat yalnız yeni element əlavə edir və mövcud elementləri silmir. $m < n$ olduğu üçün massivin ölçüsünü azaltmaq mümkün deyil.]
  ),
)

#table(
  columns: (auto, 0.3fr, 1fr),
  [*Giriş*], [*Çıxış*], [*İzah*],
  ..examples.map(
    example => (
      text(example.at(0), font: "Cascadia Code", size: 11pt),
      text(example.at(1), font: "Cascadia Code", size: 11pt),
      text(example.at(2), size: 11.5pt)
    )
  ).flatten()
)

#pagebreak()

== Qiymətləndirmə

Bu məsələ aşağıdakı kimi 6 alt tapşırıqdan ibarətdir:

#table(
  align: center + horizon,
  columns: (auto, 1fr, 1fr),
  [*Alt tapşırıq*], [*Əlavə məhdudiyyətlər*], [*Bal*],
  [0], [Nümunələr], [0 bal],
  [1], [$n, m <= 9$], [10 bal],
  [2], [Əgər cavab `YES`-dirsə, onda $a$ massivinin istənilən iki qonşu ilkin elementi arasında ən çox bir əlavə etmə əməliyyatı yerinə yetirilir.], [10 bal],
  [3], [$n = 2$], [15 bal],
  [4], [$n, m <= 2000$], [20 bal],
  [5], [Bütün $1 <= i <= n$ üçün $a_i = 1$], [15 bal],
  [6], [Əlavə məhdudiyyət yoxdur], [30 bal]
)