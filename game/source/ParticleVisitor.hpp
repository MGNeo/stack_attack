#pragma once

namespace sa
{
  class Dust;
  class Shard;
  class Coin;

  class ParticleVisitor
  {
  public:

    virtual void visit(Dust& _dust) = 0;
    //virtual void visit(Shard& _shard) = 0;
    //virtual void visit(Coin& _coin) = 0;

  };
}
