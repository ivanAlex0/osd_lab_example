#include "semaphore.h"
#include "assert.h"

void
SemaphoreInit(
    OUT     PSEMAPHORE      Semaphore,
    IN      DWORD           InitialValue
)
{
    ASSERT(NULL != Semaphore);
    ASSERT(InitialValue > 0);

    Semaphore->Value = InitialValue;
}

void
SemaphoreDown(
    INOUT   PSEMAPHORE      Semaphore,
    IN      DWORD           Value
)
{
    ASSERT(NULL != Semaphore);
    ASSERT(Value > 0);

    INTR_STATE dummyState;

    LockAcquire(&Semaphore->SemaphoreLock, &dummyState);
    Semaphore->Value -= Value;
    LockRelease(&Semaphore->SemaphoreLock, dummyState);
}

void
SemaphoreUp(
    INOUT   PSEMAPHORE      Semaphore,
    IN      DWORD           Value
)
{
    ASSERT(NULL != Semaphore);
    ASSERT(Value > 0);

    INTR_STATE dummyState;

    LockAcquire(&Semaphore->SemaphoreLock, &dummyState);
    Semaphore->Value += Value;
    LockRelease(&Semaphore->SemaphoreLock, dummyState);
}