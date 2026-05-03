// ready

#import "/templateDay2-AZ.typ": *

#show: project.with(
  title: "Tor və Toplar 1",
  time_limit: 0.5,
  memory_limit: 256
)

$n times m$ ölçülü tor verilir. Siz yuxarı-sol xanadan $(1, 1)$ başlayırsınız və aşağı-sağ xanaya $(n, m)$ çatmalısınız. Dörd istiqamətdə hərəkət edə bilərsiniz: yuxarı, aşağı, sola və ya sağa, hər birinin xərci $1$-dir.

Bundan əlavə, $k$ xanada top yerləşdirilib. Əgər top olan xanaya daxil olsanız, bu top ilə eyni sətirdə və ya sütunda olan istənilən başqa xanaya $1$ xərc çəkərək dərhal hərəkət edə bilərsiniz. Top *sizinlə birlikdə təyinat xanasına hərəkət edir* və sonra əvvəlki mövqeyinə geri *qayıtmır*. Eyni topu təkrar istifadə edə bilərsiniz.

Bu o deməkdir ki:

$(r, c)$ xanasında top varsa, və siz həmin xanadasınızsa, top ilə birlikdə $(1 <= x <= n)$ şərtini ödəyən istənilən $x$ sətri üçün $(x, c)$ xanasına və ya $(1 <= y <= m)$ şərtini ödəyən istənilən $y$ sütunu üçün $(r, y)$ xanasına dərhal hərəkət edə bilərsiniz və top da bu hərəkətdən sonra həmin xanada qalır.

$(1, 1)$ xanasından $(n, m)$ xanasına çatmaq üçün tələb olunan minimum toplam xərci tapın.

== Giriş
İlk sətirdə bir tam ədəd $t$ ($1 <= t <= 10^4$) — testlərin sayı verilir.

Daha sonra hər bir test üçün:

--- Birinci sətirdə üç tam ədəd $n$, $m$ və $k$ ($1 <= n, m <= 10^9$, $0 <= k <= min(n dot m, 10^5)$) verilir --- müvafiq olaraq sətirlərin, sütunların və topların sayı.

--- Növbəti $k$ sətrin hər birində iki tam ədəd $r_i$ və $c_i$ ($1 <= r_i <= n$, $1 <= c_i <= m$) verilir --- $i$-ci topun yerləşdiyi sətir və sütun. Girişdəki bütün topların fərqli xanada olduğuna zəmanət verilir.

Bütün testlər üzrə $k$-ların cəminin $10^5$-i aşmadığına zəmanət verilir.

== Çıxış
Hər bir test üçün yeni sətirdən tək bir tam ədəd --- $(1, 1)$ xanasından $(n, m)$ xanasına çatmaq üçün tələb olunan minimum toplam xərci çap edin.

== Məhdudiyyətlər
- $1 <= t <= 10^4$
- $1 <= n, m <= 10^9$
- $0 <= k <= min(n dot m, 10^5)$, $sum k <= 10^5$
- $1 <= r_i <= n$
- $1 <= c_i <= m$
- alt tapşırıqlar üçün qiymətləndirmə bölməsinə baxın.

#pagebreak()

== Nümunələr

// Input, Output, Explanation
#let examples = (
  (
  "4
2 2 0
2 2 1
1 2
3 3 2
1 2
2 3
5 5 3
1 3
3 3
5 3",

  "2
2
3
4",

  [Birinci testdə torun ölçüsü $2 times 2$-dir və heç bir top yoxdur, buna görə yalnız adi hərəkətlərlə başlanğıcdan sona çatılır.

İkinci testdə torun ölçüsü yenə $2 times 2$-dir və $(1, 2)$ xanasında yerləşən bir top var.

Üçüncü testdə $3 times 3$ ölçülü torda iki top var: $(1, 2)$ və $(2, 3)$ xanalarında.

Dördüncü testdə $5 times 5$ ölçülü torda üç top $(1, 3)$, $(3, 3)$ və $(5, 3)$ xanalarında yerləşir.]
  ),
)

#table(
  columns: (auto, auto, 1fr),
  [*Giriş*], [*Çıxış*], [*İzah*],
  ..examples.map(
    example => (
      text(example.at(0), font: "Cascadia Code", size: 10.5pt),
      text(example.at(1), font: "Cascadia Code", size: 10.5pt),
      text(example.at(2), size: 12pt)
    )
  ).flatten()
)
== Qiymətləndirmə

Bu məsələdə 20 test var və hər testə görə 5 bal verilir. 

Nümunə testləri əsas testlərə daxil deyil.