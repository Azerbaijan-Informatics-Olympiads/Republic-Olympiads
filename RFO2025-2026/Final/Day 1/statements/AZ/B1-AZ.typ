// ready

// junior only
#import "/templateDay1-AZ.typ": *

#show: project.with(
  title: "Piyadaları Yerləşdirin",
  time_limit: 3,
  memory_limit: 256
)

Sizə xanaları tam ədədli $(x, y)$ koordinatları ilə müəyyən edilən nəhəng şahmat taxtası verilir. Taxta aşağı sol küncdən $(1, 1)$ yuxarı sağ küncə $(2026, 2026)$ qədər uzanır.

Siz taxtaya çoxlu piyada yerləşdirməlisiniz. 

$(x_1, y_1)$ və $(x_2, y_2)$ koordinatlarında yerləşdirilmiş istənilən iki piyada arasındakı məsafə Manhetten məsafəsi ilə ölçülür:
$ d = |x_1 - x_2| + |y_1 - y_2| $

Tapşırığınız taxtaya piyadaları elə yerləşdirməkdir ki, bütün piyada cütləri arasındakı Manhetten məsafələri bir-birindən fərqli olsun. Heç bir iki piyada eyni xanada yerləşə bilməz. Məqsədiniz taxtaya qoyulan piyadaların sayını ($P$) maksimallaşdırmaqdır.

== Giriş
#text(fill: red)[_Bu məsələdə giriş verilənləri yoxdur._]

== Çıxış
Çıxışın ilk sətrində, yerləşdirəcəyiniz piyadaların sayını bildirən tək bir tam ədəd $P$ ($P >= 1$) çap edin. 

Növbəti $P$ sətrin hər birində piyadaların yerləşdirildiyi xanaları bildirən, boşluqla ayrılmış iki tam ədəd $x_i$ və $y_i$ ($1 <= x_i, y_i <= 2026$) çap edin.

== Nümunə

// Input, Output, Explanation
#let examples = (
  (
  "3
1 1
2 1
5 1",
  
  [$P=3$ piyadadan ibarət düzgün çıxış nümunəsi verilmişdir.
  Burada müxtəlif 3 cüt var və istənilən cüt piyada arasındakı Manhetten məsafəsi fərqlidir.

$d_(1,2) = |1 - 2| + |1 - 1|=1$

$d_(1,3) = |1 - 5| + |1 - 1|=4$

$d_(2,3) = |2 - 5| + |1 - 1|=3$]
  ),
)

#table(
  columns: (auto, 1fr),
   [*Çıxış*], [*İzah*],
  ..examples.map(
    example => (text(example.at(0), font: "Cascadia Code"), example.at(1)) 
  ).flatten()
)


== Qiymətləndirmə
$P$ sayda piyadadan ibarət düzgün konfiqurasiya üçün balınız aşağıdakı qaydada hesablanır:

- Əgər $P>=50$ olarsa, $100$ bal.
- $1<=P<50$ olarsa, $2 times P$ bal.

Maksimum $100$ bal toplamaq üçün siz $P >= 50$ piyadanı düzgün yerləşdirməlisiniz. 

Əgər eyni xanaya birdən çox piyada yerləşdirsəniz, hər hansı piyadanı taxtanın sərhədlərindən kənara yerləşdirsəniz yaxud hər hansı iki piyada cütü eyni Manhetten məsafəsinə malik olarsa bu halda balınız $0$ olacaq.
