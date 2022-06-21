/*
 * Created by okn-yu on 2022/06/13.
 */

/*
 * レイトレーシングの扱う対象:
 * レイトレーシングで計算を行うのは光の強さ
 * 光の強さは放射エネルギーとして定式化される
 *
 * 放射エネルギー:
 * 波長λに光子がn_λ個ある仮定する場合に全エネルギーは (n_λ * h * c)/λ として表される
 * 上の式を全波長に関して積分したものが放射エネルギー
 * つまり各波長にn_λ個の光子が含まれる光のエネルギー
 * 結局の所光とは"特定の波長の光子の集合"であり、方向性を持つエネルギーの塊である
 *
 * 放射束:
 * 単位時間当たりの放射エネルギー
 * 物理的には単位時間当たりにある領域を通過する光子の数として解釈できる
 * 実際にレイトレーシングで画像を計算する場合はRGB相当の波長の放射束を計算する
 * 計算結果をRGBの色にマッピングを行う
 * TODO:以下を今後のお実装で意識すること
 * 放射束の下限は0だが上限は無限大である
 * 一方RGBのカラーは0-255という上限が存在する
 * 同じ波動でも音の大きさには上限がないが、色には上限が存在する
 * どこかで閾値があってそれ以上は認識できないのかもしれない
 *
 * 放射束面密度:
 * 単位面積当たりの放射束
 * つまり単位時間に単位面積を通過する光子の個数
 *
 * 放射照度:
 * 入射してくる光に関する放射束面密度
 *
 * 放射発散度:
 * 出射する光に関する放射束面密度
 *
 *  立体角:
 *  ある領域Sを半径1の単位球面上に投影した面積の大きさのこと（平面角ラジアンの3次元版）
 *  平面角は円弧の長さだが立体角は円錐となる
 *  この円錐の底面の面積が立体角に相当する
 *  定義から立体角の最大値は4πで最小値は0となる
 *  面積の大きさを0に近づけることで微小立体角が得られる
 *  微小立体角を考えると円錐の底面は点となるので、微小立体角は3次元上での方向を表す
 *  （面に関しては方向は定義できないが面積0の点では方向が定義できる）
 *
 *  参考
 *　https://batapara.com/archives/solid-angle.html/
 *
 * 放射輝度:
 * 単位立体角あたりの単位投影面積あたりの放射束
 * 立体角は単位球の面積に相当するので放射束密度の立体角版に相当する
 * 単位投影面積は放射束と法線とのなす角度のcos倍することで得られる
 * 物理的にはw方向から注目する点に単位時間あたりに飛来した法線とのなす角度で補正した光子の総数
 *
 * BRDF:双方向反射率分布関数
 * f(x, w_i, w_o)の解釈
 * 点xにw_i方向から入射した光が、w_o方向に反射される光の割合
 * 入射に関しては法線とのなす角度cosの補正がかかるが、出射にはかからない（分子は放射束で分母は放射輝度）
 * 物体表面の反射特性を表しており、物体のマットな質感や光沢はこのBRDFを用いて表現される
 * 放射輝度の放射照度に関する微分として定義される（分子が反射で分母が入射）
 *
 * BRDFの特性
 * w_iとw_oに関して対称（すなわち入射と出射は反転しても同じ結果）
 * 半球の立体角で積分した結果は1以下（入射以上の反射はない）
 * BRDFに放射輝度を掛けて半球の立体角で積分すると、ある点xに全方向から入射した光が、特定の方向にどの程度反射したかを計算することができる
 *
 * BRDFの使い方
 * 光の反射する点xは固定
 * 法線nも固定
 * 最終的な出力のw_oは固定
 * w_oとnのなす角度θは固定
 * w_iは半球全体を考える
 *
 * すなわち"反射する点全体に入射するあらゆる角度からの光を考慮して特定の視線方向への反射する光を計算する"
 * L(w_r, x) = integral ( f(x, w_i, w_r) * L(w_i, x) * cos(theta)) dw
 *
 * 1. 視線方向にある点から反射する光を計算したい
 * 2. その点に入射するあらゆる方向からの光を考慮する必要がある
 * 3. 2.の計算には各入射光ごとにbrdfと入射光の放射輝度を積算しcos(theta)で補正をかけ合わせた結果を合算する
 *
 * cos(theta)の解釈: 視線と法線が直交していれば反射はしないため0となる
 *
 * 注意:
 * brdfは波長（RGB）毎の反射率に相当するのでその出力はベクトル
 *
 * 注意:
 * 物体表面に固有の色があるわけではない
 * 人間が視覚で認識する"色"は、物体表面で入射光の各波長をどの程度反射するかに依存する
 * そして入射光の反射率はBRDFにより決定される
 * そのためbase_colorの影響はBRDFに現れる
 *
 */

#ifndef PRACTICEPATHTRACING_BRDF_HPP
#define PRACTICEPATHTRACING_BRDF_HPP

#endif //PRACTICEPATHTRACING_BRDF_HPP