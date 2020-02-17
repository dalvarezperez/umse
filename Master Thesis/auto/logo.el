(TeX-add-style-hook
 "logo"
 (lambda ()
   (TeX-run-style-hooks
    "graphicx")
   (TeX-add-symbols
    '("ETHlogo" ["argument"] 0))
   (LaTeX-add-environments
    '("remark" LaTeX-env-args ["argument"] 0)
    '("example" LaTeX-env-args ["argument"] 0)
    '("definition" LaTeX-env-args ["argument"] 0)))
 :latex)

