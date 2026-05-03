// The project function defines how your document looks.
// It takes your content and some metadata and formats it.
// Go ahead and customize it to your liking!
#let project(title: "", time_limit: 0, memory_limit: 0, body) = {
  // Set the document's basic properties.
  set document(title: title)

  set page(numbering: "1", number-align: center, header: grid(columns: (1fr, auto), [Respublika İnformatika Olimpiadası – Final Turu, 2-ci Gün], [02 May 2026])
  )

  set text(font: "Libertinus Serif", lang: "az", hyphenate: false, size: 12pt)

  // Title row.
  align(center)[
    #block(text(weight: 700, 1.75em, title))
  ]

  if time_limit > 0 {
   align(center)[
      _Zaman limiti: #time_limit san._
    ]
  }
  
  if memory_limit > 0 {
    v(-5pt)
    align(center)[
      _Yaddaş limiti: #memory_limit mb._
    ]
  }

  // Main body.
  set par(justify: true)

  
  set list(
    indent: 1em,
    body-indent: 0.5em
  )

  set enum(
    indent: 1em,
    body-indent: 0.5em
  )
  
  body
}