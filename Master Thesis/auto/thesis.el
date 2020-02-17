(TeX-add-style-hook
 "thesis"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("memoir" "11pt" "a4paper" "titlepage")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("fontenc" "OT1") ("babel" "english") ("inputenc" "utf8") ("mathpazo" "sc") ("ntheorem" "amsmath" "thmmarks") ("hyperref" "linkcolor=black" "colorlinks=true" "citecolor=black" "filecolor=black")))
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "extrapackages"
    "layoutsetup"
    "theoremsetup"
    "macrosetup"
    "abstract"
    "introduction"
    "malware"
    "umse"
    "conclusions"
    "memoir"
    "memoir11"
    "fontenc"
    "babel"
    "inputenc"
    "mathpazo"
    "amsmath"
    "amssymb"
    "amsfonts"
    "mathrsfs"
    "ntheorem"
    "graphicx"
    "soul"
    "pdfpages"
    "hyperref")
   (LaTeX-add-bibliographies
    "refs"))
 :latex)

