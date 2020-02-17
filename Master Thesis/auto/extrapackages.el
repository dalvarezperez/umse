(TeX-add-style-hook
 "extrapackages"
 (lambda ()
   (LaTeX-add-environments
    '("remark" LaTeX-env-args ["argument"] 0)
    '("example" LaTeX-env-args ["argument"] 0)
    '("definition" LaTeX-env-args ["argument"] 0)))
 :plain-tex)

