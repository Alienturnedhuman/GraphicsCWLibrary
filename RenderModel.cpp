//
// Created by Ben Dickson on 5/4/17.
//

#include "RenderModel.h"





inline void RenderPipeline::addModel(RenderModel* model)
{
    pipeline.push_back(model);
    ++size;
}
inline RenderModel* RenderPipeline::retrieveModel()
{
    if(size==0)
    {
        return nullptr;
    }
    RenderModel* r = pipeline.back();
    pipeline.pop_back();
    --size;
    return r;
}