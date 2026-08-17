#ifndef _KNN_HPP_
#define _KNN_HPP_

#include "population.hpp"

#include <vector>

/**
 * Population内のtarget_index番目の個体に近い個体をk個返す。
 *
 * 距離計算にはIndividual::xのみを使用する。
 * target_index番目の個体自身は候補から除外する。
 *
 * 戻り値のIndividualはPopulation内の個体のコピー。
 */
std::vector<Individual> findKNearestIndividuals(
    const Population &population,
    int target_index,
    int k);

/**
 * 任意のIndividualに近いPopulation内の個体をk個返す。
 *
 * 距離計算にはIndividual::xのみを使用する。
 * targetがPopulation外の子個体などの場合に使用する。
 *
 * 戻り値のIndividualはPopulation内の個体のコピー。
 */
std::vector<Individual> findKNearestIndividuals(
    const Population &population,
    const Individual &target,
    int k);

#endif