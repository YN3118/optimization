#include "knn.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace
{

    // xベクトル間のユークリッド距離の二乗
    double squaredEuclideanDistance(
        const std::vector<double> &x1,
        const std::vector<double> &x2)
    {
        if (x1.size() != x2.size())
        {
            throw std::invalid_argument(
                "squaredEuclideanDistance: "
                "xベクトルの次元数が一致していません。");
        }

        double squared_distance = 0.0;

        for (std::size_t d = 0; d < x1.size(); ++d)
        {
            const double difference = x1[d] - x2[d];
            squared_distance += difference * difference;
        }

        return squared_distance;
    }

    // 近傍候補を管理する内部構造体
    struct NeighborCandidate
    {
        int index;
        double squared_distance;
    };

    // 候補から距離が近いIndividualをk個返す
    std::vector<Individual> selectKNearestIndividuals(
        const Population &population,
        std::vector<NeighborCandidate> &candidates,
        int k)
    {
        if (k <= 0 || candidates.empty())
        {
            return {};
        }

        const std::size_t selected_count = std::min(
            static_cast<std::size_t>(k),
            candidates.size());

        // 距離が近いk個を先頭に並べる
        std::partial_sort(
            candidates.begin(),
            candidates.begin() + selected_count,
            candidates.end(),
            [](const NeighborCandidate &left,
               const NeighborCandidate &right)
            {
                if (left.squared_distance != right.squared_distance)
                {
                    return left.squared_distance <
                           right.squared_distance;
                }

                // 距離が同じ場合はインデックスが小さい個体を優先
                return left.index < right.index;
            });

        std::vector<Individual> nearest_individuals;
        nearest_individuals.reserve(selected_count);

        for (std::size_t i = 0; i < selected_count; ++i)
        {
            const int index = candidates[i].index;

            // Population内のIndividualをコピーして追加
            nearest_individuals.push_back(
                population.at(index));
        }

        return nearest_individuals;
    }

} // namespace

std::vector<Individual> findKNearestIndividuals(
    const Population &population,
    int target_index,
    int k)
{
    if (population.empty())
    {
        throw std::invalid_argument(
            "findKNearestIndividuals: Populationが空です。");
    }

    if (target_index < 0 ||
        target_index >= population.size())
    {
        throw std::out_of_range(
            "findKNearestIndividuals: "
            "target_indexが範囲外です。");
    }

    if (k <= 0)
    {
        return {};
    }

    const Individual &target =
        population.at(target_index);

    if (target.x.empty())
    {
        throw std::invalid_argument(
            "findKNearestIndividuals: "
            "対象個体のxベクトルが空です。");
    }

    std::vector<NeighborCandidate> candidates;
    candidates.reserve(
        static_cast<std::size_t>(
            population.size() - 1));

    for (int i = 0; i < population.size(); ++i)
    {

        const Individual &candidate =
            population.at(i);

        const double squared_distance =
            squaredEuclideanDistance(
                target.x,
                candidate.x);

        candidates.push_back(
            {i,
             squared_distance});
    }

    return selectKNearestIndividuals(
        population,
        candidates,
        k);
}

std::vector<Individual> findKNearestIndividuals(
    const Population &population,
    const Individual &target,
    int k)
{
    if (population.empty())
    {
        throw std::invalid_argument(
            "findKNearestIndividuals: Populationが空です。");
    }

    if (target.x.empty())
    {
        throw std::invalid_argument(
            "findKNearestIndividuals: "
            "対象個体のxベクトルが空です。");
    }

    if (k <= 0)
    {
        return {};
    }

    std::vector<NeighborCandidate> candidates;
    candidates.reserve(
        static_cast<std::size_t>(
            population.size()));

    for (int i = 0; i < population.size(); ++i)
    {
        const Individual &candidate =
            population.at(i);

        const double squared_distance =
            squaredEuclideanDistance(
                target.x,
                candidate.x);

        candidates.push_back(
            {i,
             squared_distance});
    }

    return selectKNearestIndividuals(
        population,
        candidates,
        k);
}